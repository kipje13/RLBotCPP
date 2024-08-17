#include "flatbuffers/buffer.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <flatbuffers/flatbuffers.h>

#include <iostream>

#include <memory>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <rlbot_generated.h>
#include <sys/types.h>
#include <tuple>
#include <utility>
#include <vector>

enum PacketType : uint16_t {
    None,
    // Arrives at a high rate according to https://wiki.rlbot.org/botmaking/tick-rate/ except
    // "desired tick rate" is not relevant here
    GameTickPacket,

    // Sent once when a match starts, or when you first connect.
    FieldInfo,

    // Sent once when a match starts, or when you first connect.
    StartCommand,
    MatchSettings,
    PlayerInput,
    DesiredGameState,
    RenderGroup,
    RemoveRenderGroup,
    MatchComms,

    // Sent every time the ball diverges from the previous prediction,
    // or when the previous prediction no longer gives a full 6 seconds into the future
    BallPrediction,

    // Clients must send this after connecting to the socket.
    ReadyMessage,

    // used to end a match and shut down bots (optionally the server as well)
    StopCommand
};

class TcpSocket
{
private:
    int m_socket;
    std::string m_ip_address;
    uint16_t m_port; 

public:
    TcpSocket(const std::string& ip_address, uint16_t port) : m_ip_address(ip_address), m_port(port)
    {
        m_socket = ::socket(AF_INET, SOCK_STREAM, 0);

        if (m_socket < 0)
            throw std::runtime_error("Socket exception: " + std::string(::strerror(m_socket)));
    }

    void connect()
    {
        struct sockaddr_in server_addr = {0};
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = ::inet_addr(m_ip_address.c_str());
        server_addr.sin_port = ::htons(m_port);

        int ret = ::connect(m_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

        if (ret < 0)
            throw std::runtime_error("Socket exception: " + std::string(::strerror(ret)));
    }

    void send(const void *buffer, size_t len)
    {
        int ret = ::send(m_socket, buffer, len, 0);

        if (ret < 0)
            throw std::runtime_error("Socket exception: " + std::string(::strerror(ret)));
    }

    void receive(void * buffer, size_t len)
    {
        int ret = ::recv(m_socket, buffer, len, 0);

        if (ret == 0)
            throw std::runtime_error("Socket closed by remote endpoint");

        if (ret < 0)
            throw std::runtime_error("Socket exception: " + std::string(::strerror(ret)));
    }
};

class Interface {
private:
    std::unique_ptr<TcpSocket> m_socket;

    struct packet_header {
        uint16_t type;
        uint16_t length;
    };

public:
    Interface(std::string ip_address, uint16_t port) : m_socket(std::make_unique<TcpSocket>(ip_address, port))
    {
    }

    void connect()
    {
        m_socket->connect();
    }

    void send_packet(PacketType type, void *buffer, uint16_t len)
    {
        uint16_t data;
        
        data = ::htons(type);
        m_socket->send(&data, sizeof(data));
        
        data = ::htons(len);
        m_socket->send(&data, sizeof(data));

        m_socket->send(buffer, len);
    }

    std::tuple<PacketType, std::vector<uint8_t>> receive_packet()
    {
        packet_header header;

        m_socket->receive(&header, sizeof(header));

        uint16_t len = ::ntohs(header.length);
        
        std::vector<uint8_t> data(len);

        m_socket->receive(&data.front(), len);

        return std::make_tuple((PacketType)::ntohs(header.type), data);
    }
};

int main()
{
    Interface client("127.0.0.1", 23234);
    client.connect();

    auto player1 = std::make_unique<rlbot::flat::PlayerConfigurationT>();
    player1->variety.type = rlbot::flat::PlayerClass_RLBot;
    player1->name = "Bot";
    player1->team = 0;
    player1->spawn_id = 0;

    auto player2 = std::make_unique<rlbot::flat::PlayerConfigurationT>();
    player2->variety.type = rlbot::flat::PlayerClass_Human;
    player2->name = "Human";
    player2->team = 1;
    player2->spawn_id = 1;

    rlbot::flat::MatchSettingsT matchsettings;
    matchsettings.game_mode = rlbot::flat::GameMode_Soccer;
    matchsettings.game_map_upk = "Stadium_P";
    matchsettings.instant_start = true;
    matchsettings.player_configurations.push_back(std::move(player1));
    matchsettings.player_configurations.push_back(std::move(player2));
    matchsettings.existing_match_behavior = rlbot::flat::ExistingMatchBehavior_Restart;
    matchsettings.enable_rendering = true;
    matchsettings.mutator_settings = std::make_unique<rlbot::flat::MutatorSettingsT>();
    matchsettings.mutator_settings->match_length = rlbot::flat::MatchLength_Unlimited;
    matchsettings.auto_start_bots = true;
    
    flatbuffers::FlatBufferBuilder fbb(0x10000);
    fbb.Finish(rlbot::flat::MatchSettings::Pack(fbb, &matchsettings));

    client.send_packet(MatchSettings, fbb.GetBufferPointer(), fbb.GetSize());

    fbb.Clear();

    rlbot::flat::ReadyMessageT connection_settings;
    connection_settings.close_after_match = true;
    connection_settings.wants_ball_predictions = true;
    connection_settings.wants_comms = true;

    fbb.Finish(rlbot::flat::ReadyMessage::Pack(fbb, &connection_settings));

    client.send_packet(ReadyMessage, fbb.GetBufferPointer(), fbb.GetSize());

    while (true) 
    {
        auto [packet_type, data] = client.receive_packet();

        if (packet_type == GameTickPacket)
        {
            auto packet = flatbuffers::GetRoot<rlbot::flat::GameTickPacket>(&data.front());

            std::cout << packet->game_info()->seconds_elapsed() << std::endl;
        }

    }

    return 0;
}

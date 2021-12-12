#pragma once
#include "easywsclient.hpp"
#include "json.hpp"

namespace rlbot {
    class MatchCommsClient {
        easywsclient::WebSocket::pointer client;

    public:
        explicit MatchCommsClient(const std::string& url) {
            client = easywsclient::WebSocket::from_url(url + "/broadcast");
        }

        ~MatchCommsClient() {
            client->close();
            delete client;
        }

        std::vector<nlohmann::json> GetIncomingBroadcast() {
            std::vector<nlohmann::json> messages;
            client->poll();
            client->dispatch([&messages](const std::string& message) {
                messages.push_back(nlohmann::json::parse(message));
            });
            return messages;
        }

        void Send(const nlohmann::json & message) {
            client->send(message.dump());
            client->poll();
        }
    };
}

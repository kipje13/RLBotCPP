#pragma once
#include "rlbot/interface.h"
#include "rlbot/packets.h"
#include "rlbot/rlbot_generated.h"

#include "tmcp.hpp"
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

#include <string>

using server = websocketpp::server<websocketpp::config::asio>;

namespace rlbot {
class Bot {
private:
  int lastMessageIndex = -1;

public:
  int index;
  int team;
  std::string name;
  server matchcomms_connection;

  Bot(int index, int team, std::string name, std::string uri = std::string());
  virtual ~Bot() {}
  virtual Controller GetOutput(GameTickPacket gametickpacket) = 0;

  BallPrediction GetBallPrediction();
  FieldInfo GetFieldInfo();
  MatchInfo GetMatchInfo();
  MatchComms::Packet GetMatchComms();

  void SendQuickChat(rlbot::flat::QuickChatSelection message, bool teamOnly);
  QuickChatMessages ReceiveQuickChat();
};
} // namespace rlbot

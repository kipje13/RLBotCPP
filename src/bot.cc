#include "rlbot/bot.h"

#include <vector>

#include "rlbot/interface.h"
#include "rlbot/rlbot_generated.h"

#include "json.hpp"

using message_ptr = server::message_ptr;

namespace rlbot {
Bot::Bot(int _index, int _team, std::string _name, std::string uri) {
  index = _index;
  team = _team;
  name = _name;
}

BallPrediction Bot::GetBallPrediction() {
  ByteBuffer buffer = Interface::GetBallPrediction();
  BallPrediction ballprediction(buffer);
  Interface::Free(buffer.ptr);
  return ballprediction;
}

FieldInfo Bot::GetFieldInfo() {
  ByteBuffer buffer = Interface::UpdateFieldInfoFlatbuffer();
  FieldInfo fieldinfo(buffer);
  Interface::Free(buffer.ptr);
  return fieldinfo;
}

MatchInfo Bot::GetMatchInfo() {
  ByteBuffer buffer = Interface::GetMatchSettings();
  MatchInfo matchinfo(buffer);
  Interface::Free(buffer.ptr);
  return matchinfo;
}

MatchComms::Packet Bot::GetMatchComms() {
  server matchcomms_connection; 
  matchcomms_connection.set_message_handler([](websocketpp::connection_hdl hdl, message_ptr msg){
    // ...
  });
  return MatchComms::Packet{};
}

void Bot::SendQuickChat(rlbot::flat::QuickChatSelection message,
                        bool teamOnly) {
  Interface::SendQuickChat(message, index, teamOnly);
}

QuickChatMessages Bot::ReceiveQuickChat() {
  ByteBuffer buffer =
      Interface::ReceiveQuickChat(index, team, lastMessageIndex);
  QuickChatMessages quickchat = QuickChatMessages(buffer);
  Interface::Free(buffer.ptr);

  int count = quickchat->messages()->size();

  if (count > 0) {
    lastMessageIndex = quickchat->messages()->Get(count - 1)->messageIndex();
  }

  return quickchat;
}
} // namespace rlbot

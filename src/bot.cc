#include "rlbot/bot.h"

#include <vector>

#include "rlbot/interface.h"
#include "rlbot/rlbot_generated.h"

namespace rlbot {
Bot::Bot(int _index, int _team, std::string _name) {
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

#include "bot.h"

#include <vector>

#include "interface.h"
#include "rlbot_generated.h"

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
} // namespace rlbot

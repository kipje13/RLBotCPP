#pragma once
#include "flatbuffercontainer.h"
#include "interface.h"
#include "rlbot_generated.h"

#include <string>

namespace rlbot {
class Bot {
public:
  int index;
  int team;
  std::string name;

  Bot(int index, int team, std::string name);
  virtual ~Bot() {}
  virtual Controller GetOutput(GameTickPacket gametickpacket) = 0;

  BallPrediction GetBallPrediction();
  FieldInfo GetFieldInfo();
  MatchInfo GetMatchInfo();

  void SendQuickChat(rlbot::flat::QuickChatSelection message, bool teamOnly);
};
} // namespace rlbot

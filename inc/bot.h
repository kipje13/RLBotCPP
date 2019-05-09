#pragma once
#include "interface.h"
#include "rlbot_generated.h"

#include "simulation/game.h"

#include <string>

class Bot {
 public:
  int index;
  int team;
  std::string name;

  Game gameInfo = Game(0, 0);

  Bot(int index, int team, std::string name);
  virtual Input GetOutput(
      const rlbot::flat::GameTickPacket* gameTickPacket,
      const rlbot::flat::FieldInfo* fieldInfo,
      const rlbot::flat::BallPrediction* ballPrediction);

  void SendQuickChat(rlbot::flat::QuickChatSelection message, bool teamOnly);

  void ReadGameTickPacket(const rlbot::flat::GameTickPacket* gameTickPacket);
};

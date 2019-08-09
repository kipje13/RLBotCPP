#pragma once
#include "interface.h"
#include "rlbot_generated.h"

#include <string>

namespace rlbotcpp {
class Bot {
public:
  int index;
  int team;
  std::string name;

  Bot(int index, int team, std::string name);
  virtual Controller
  GetOutput(const rlbot::flat::GameTickPacket *gameTickPacket,
            const rlbot::flat::FieldInfo *fieldInfo,
            const rlbot::flat::BallPrediction *ballPrediction);

  void SendQuickChat(rlbot::flat::QuickChatSelection message, bool teamOnly);
};
} // namespace rlbotcpp

#pragma once

namespace rlbot {
struct Controller {
  float throttle;
  float steer;
  float pitch;
  float yaw;
  float roll;
  bool jump;
  bool boost;
  bool handbrake;
  bool useItem;
};
} // namespace rlbot

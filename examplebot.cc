#include "examplebot.h"

#include <string>

#include "bot.h"
#include "rlbot_generated.h"

ExampleBot::ExampleBot(int _index, int _team, std::string _name)
    : Bot(_index, _team, _name) {

}

Input ExampleBot::GetOutput(
    const rlbot::flat::GameTickPacket* gameTickPacket,
    const rlbot::flat::FieldInfo* fieldInfo,
    const rlbot::flat::BallPrediction* ballPrediction) {
  Input controller{0};

  vec3 local = dot(transpose(gameInfo.cars[index].o), gameInfo.ball.x - gameInfo.cars[index].x);

  if (local[1] > 0)
	  controller.steer = 1;
  else
	  controller.steer = -1;

  controller.throttle = 1.0f;

  return controller;
}

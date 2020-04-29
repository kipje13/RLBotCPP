#include "rlbot/statesetting.h"
#include "rlbot/interface.h"

namespace rlbot {
flatbuffers::Offset<rlbot::flat::Vector3Partial>
createVector3Partial(flatbuffers::FlatBufferBuilder &builder,
                     std::optional<DesiredVector3> vector3) {
  if (vector3.has_value()) {
    auto x = rlbot::flat::Float(vector3.value().x);
    auto y = rlbot::flat::Float(vector3.value().y);
    auto z = rlbot::flat::Float(vector3.value().z);
    return rlbot::flat::CreateVector3Partial(builder, &x, &y, &z);
  } else {
    return 0;
  }
}

flatbuffers::Offset<rlbot::flat::RotatorPartial>
createRotatorPartial(flatbuffers::FlatBufferBuilder &builder,
                     std::optional<DesiredRotator> rotator) {
  if (rotator.has_value()) {
    auto p = rlbot::flat::Float(rotator.value().pitch);
    auto y = rlbot::flat::Float(rotator.value().yaw);
    auto r = rlbot::flat::Float(rotator.value().roll);
    return rlbot::flat::CreateRotatorPartial(builder, &p, &y, &r);
  } else {
    return 0;
  }
}

PhysicsState::PhysicsState() {}

flatbuffers::Offset<rlbot::flat::DesiredPhysics>
PhysicsState::BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder) {
  auto ballLocationOffset = createVector3Partial(builder, location);
  auto ballRotationOffset = createRotatorPartial(builder, rotation);
  auto ballVelocityOffset = createVector3Partial(builder, velocity);
  auto ballAngularVelocityOffset =
      createVector3Partial(builder, angularVelocity);

  auto ballPhysicsOffset = rlbot::flat::CreateDesiredPhysics(
      builder, ballLocationOffset, ballRotationOffset, ballVelocityOffset,
      ballAngularVelocityOffset);

  return ballPhysicsOffset;
}

BallState::BallState() {}

flatbuffers::Offset<rlbot::flat::DesiredBallState>
BallState::BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder) {
  auto ballPhysicsOffset = physicsState.BuildFlatBuffer(builder);

  auto ballStateOffset =
      rlbot::flat::CreateDesiredBallState(builder, ballPhysicsOffset);

  return ballStateOffset;
}

flatbuffers::Offset<rlbot::flat::DesiredCarState>
CarState::BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder) {
  rlbot::flat::Float boost = boostAmount.value_or(0);

  auto carPhysicsOffset = physicsState.BuildFlatBuffer(builder);

  auto carStateOffset =
      rlbot::flat::CreateDesiredCarState(builder, carPhysicsOffset, boostAmount.has_value() ? &boost : nullptr);

  return carStateOffset;
}

GameState::GameState() {}

flatbuffers::Offset<rlbot::flat::DesiredGameState>
GameState::BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder) {
  auto ballStateOffset = ballState.BuildFlatBuffer(builder);

  std::vector<flatbuffers::Offset<rlbot::flat::DesiredCarState>> cars;

  for (int i = 0; i < carStates.size(); i++) {
    if (carStates[i].has_value()) {
      cars.push_back(carStates[i].value().BuildFlatBuffer(builder));
    } else {
      // Create an empty car state if this car doesn't have a desired state.
      cars.push_back(rlbot::flat::CreateDesiredCarState(builder));
    }
  }

  auto carsOffset = builder.CreateVector(cars);

  rlbot::flat::Float desiredGravity = gravity.value_or(0);
  rlbot::flat::Float desiredGameSpeed = gameSpeed.value_or(0);
  auto gameInfoState = rlbot::flat::CreateDesiredGameInfoState(builder, 
	  gravity.has_value() ? &desiredGravity : nullptr, 
	  gameSpeed.has_value() ? &desiredGameSpeed : nullptr);

  return rlbot::flat::CreateDesiredGameState(builder, ballStateOffset,
                                             carsOffset, 0, gameInfoState, 0);
}
} // namespace rlbot

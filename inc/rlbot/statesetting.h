#pragma once

#include <flatbuffers/flatbuffers.h>

#include "rlbot/rlbot_generated.h"

#include <array>
#include <optional>

namespace rlbot {
/** @brief Helper class for PhysicsState. */
struct DesiredVector3 {
  float x, y, z;
};

/** @brief Helper class for PhysicsState. */
struct DesiredRotator {
  float pitch, yaw, roll;
};

/** @brief Describes the desired state of an physics object for use in state setting. */
class PhysicsState {
public:
  /** Location of the physics object. If no value is assigned it will not modify the location when applying this physics object. */
  std::optional<DesiredVector3> location;
  /** Velocity of the physics object. If no value is assigned it will not modify the velocity when applying this physics object. */
  std::optional<DesiredVector3> velocity;
  /** Rotation of the physics object. If no value is assigned it will not modify the rotation when applying this physics object. */
  std::optional<DesiredRotator> rotation;
  /** Angular velocity of the physics object. If no value is assigned it will not modify the angular velocity when applying this physics object. */
  std::optional<DesiredVector3> angularVelocity;

  PhysicsState();

  /**
   * Creates a flatbuffers representation of this instance. This is used internally,
   * it is recommended to use Interface::SetGameState instead.
   */
  flatbuffers::Offset<rlbot::flat::DesiredPhysics>
  BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder);
};

/** @brief Describes the desired state of the ball for use in state setting. */
class BallState {
public:
  PhysicsState physicsState;

  BallState();

  /**
   * Creates a flatbuffers representation of this instance. This is used internally, 
   * it is recommended to use Interface::SetGameState instead.
   */
  flatbuffers::Offset<rlbot::flat::DesiredBallState>
  BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder);
};

/** @brief Describes the desired state of a car for use in state setting. */
class CarState {
public:
  PhysicsState physicsState;
  /** The amount of boost that the car should have after setting the state. Keeps the current boost amount if no value is assignent. */
  std::optional<float> boostAmount;

  /**
   * Creates a flatbuffers representation of this instance. This is used internally,
   * it is recommended to use Interface::SetGameState instead.
   */
  flatbuffers::Offset<rlbot::flat::DesiredCarState>
  BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder);
};

/** @brief Describes the desired state of the game. */
class GameState {
public:
  BallState ballState;
  std::array<std::optional<CarState>, 10> carStates;

  std::optional<float> gameSpeed;
  std::optional<float> gravity;

  GameState();

  /**
   * Creates a flatbuffers representation of this instance. This is used internally,
   * it is recommended to use Interface::SetGameState instead.
   */
  flatbuffers::Offset<rlbot::flat::DesiredGameState>
  BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder);
};
} // namespace rlbot

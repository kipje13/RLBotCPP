#pragma once

#include "flatbuffers/flatbuffers.h"
#include "rlbot_generated.h"

#include <array>
#include <optional>

struct DesiredVector3 {
	float x, y, z;
};

struct DesiredRotator {
	float pitch, yaw, roll;
};

class PhysicsState
{
public:
	DesiredVector3 location;
	DesiredVector3 velocity;
	DesiredRotator rotation;
	DesiredVector3 angularVelocity;

	PhysicsState();
};

class BallState
{
public:
	PhysicsState physicsState;

	BallState();
};

class CarState
{
public:
	PhysicsState physicsState;
};

class GameState
{
public:
	BallState ballState;
	std::array<std::optional<CarState>, 8> carStates;

	GameState();
	void BuildAndSend();
};
#pragma once

#include "flatbuffers/flatbuffers.h"
#include "rlbot_generated.h"

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

};

class GameState
{
public:
	BallState ballState;

	GameState();
	void BuildAndSend();
};
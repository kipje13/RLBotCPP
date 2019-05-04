#include "statesetting.h"
#include "interface.h"

#define CREATEVECTOR3PARTIAL(name, vector3) flatbuffers::Offset<rlbot::flat::Vector3Partial> name; { auto _x = &rlbot::flat::Float(vector3.x); auto _y = &rlbot::flat::Float(vector3.y); auto _z = &rlbot::flat::Float(vector3.z); name = rlbot::flat::CreateVector3Partial(builder, _x, _y, _z); }
#define CREATEROTATORPARTIAL(name, rotator) flatbuffers::Offset<rlbot::flat::RotatorPartial> name; { auto _p = &rlbot::flat::Float(rotator.pitch); auto _y = &rlbot::flat::Float(rotator.yaw); auto _r = &rlbot::flat::Float(rotator.roll); name = rlbot::flat::CreateRotatorPartial(builder, _p, _y, _r); }

PhysicsState::PhysicsState()
{
}

BallState::BallState()
{
}

GameState::GameState()
{
}

void GameState::BuildAndSend()
{
	flatbuffers::FlatBufferBuilder builder(1000);

	CREATEVECTOR3PARTIAL(ballLocationOffset, ballState.physicsState.location);
	CREATEROTATORPARTIAL(ballRotationOffset, ballState.physicsState.rotation);
	CREATEVECTOR3PARTIAL(ballVelocityOffset, ballState.physicsState.velocity);
	CREATEVECTOR3PARTIAL(ballAngularVelocityOffset, ballState.physicsState.angularVelocity);

	auto ballPhysicsOffset = rlbot::flat::CreateDesiredPhysics(builder, ballLocationOffset, ballRotationOffset, ballVelocityOffset, ballAngularVelocityOffset);
	auto ballStateOffset = rlbot::flat::CreateDesiredBallState(builder, ballPhysicsOffset);

	std::vector<flatbuffers::Offset<rlbot::flat::DesiredCarState>> cars;

	for (int i = 0; i < carStates.size(); i++)
	{
		if (carStates[i].has_value())
		{
			CREATEVECTOR3PARTIAL(carLocationOffset, carStates[i].value().physicsState.location);
			CREATEROTATORPARTIAL(carRotationOffset, carStates[i].value().physicsState.rotation);
			CREATEVECTOR3PARTIAL(carVelocityOffset, carStates[i].value().physicsState.velocity);
			CREATEVECTOR3PARTIAL(carAngularVelocityOffset, carStates[i].value().physicsState.angularVelocity);

			auto carPhysicsOffset = rlbot::flat::CreateDesiredPhysics(builder, carLocationOffset, carRotationOffset, carVelocityOffset, carAngularVelocityOffset);
			cars.push_back(rlbot::flat::CreateDesiredCarState(builder, carPhysicsOffset));
		}
		else
		{
			// Create a empty car state if this car doesn't have a desired state.
			cars.push_back(rlbot::flat::CreateDesiredCarState(builder));
		}
	}

	auto carsOffset = builder.CreateVector(cars);

	auto gameStateOffset = rlbot::flat::CreateDesiredGameState(builder, ballStateOffset, carsOffset, 0, 0);

	builder.Finish(gameStateOffset);

	Interface::SetGameState(builder.GetBufferPointer(), builder.GetSize());
}



#include "rlbot_generated.h"

#include "interface.h"
#include "namedrenderer.h"

#include <windows.h>

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define PI 3.1415

int botIndex = 0;

Controller GetOutput(const rlbot::flat::GameTickPacket* gameTickPacket);

int main(int argc, char** argv)
{
	Interface::Init("RLBot_Core_Interface_32.dll");

	while (!Interface::IsInitialized())
	{

	}

	float lasttime = 0;

	while (true)
	{
		ByteBuffer flatbufferData = Interface::UpdateLiveDataPacketFlatbuffer();

		const rlbot::flat::GameTickPacket *flatPacket = flatbuffers::GetRoot<rlbot::flat::GameTickPacket>(flatbufferData.ptr);

		if (lasttime != flatPacket->gameInfo()->secondsElapsed())
		{
			int status = Interface::SetBotInput(GetOutput(flatPacket), botIndex);

			lasttime = flatPacket->gameInfo()->secondsElapsed();
		}
		else
		{
			Sleep(1);
		}

		Interface::Free(flatbufferData.ptr);
	}
	
	return 0;
}

Controller GetOutput(const rlbot::flat::GameTickPacket* gameTickPacket)
{
	Controller controller {0};

	rlbot::flat::Vector3 ballLocation = *gameTickPacket->ball()->physics()->location();
	rlbot::flat::Vector3 carLocation = *gameTickPacket->players()->Get(botIndex)->physics()->location();
	rlbot::flat::Rotator carRotation = *gameTickPacket->players()->Get(botIndex)->physics()->rotation();

	NamedRenderer renderer("test");

	ByteBuffer bytebuffer = Interface::GetBallPrediction();

	auto ballprediction = flatbuffers::GetRoot<rlbot::flat::BallPrediction>(bytebuffer.ptr);

	renderer.StartPacket();

	std::vector<const rlbot::flat::Vector3*> points;
	
	for (int i = 0; i < ballprediction->slices()->size(); i++)
	{
		points.push_back(ballprediction->slices()->Get(i)->physics()->location());
	}

	renderer.DrawPolyLine3D(Color{0xFF, 0x00, 0x00, 0xFF}, points);

	renderer.DrawString2D("Hello world!", Color{ 0x00, 0xFF, 0x00, 0xFF }, rlbot::flat::Vector3{10,10,0}, 4, 4);
	
	renderer.FinishAndSend();

	Interface::Free(bytebuffer.ptr);


	// Calculate to get the angle from the front of the bot's car to the ball.
	double botToTargetAngle = atan2(ballLocation.y() - carLocation.y(), ballLocation.x() - carLocation.x());
	double botFrontToTargetAngle = botToTargetAngle - carRotation.yaw();
	// Correct the angle
	if (botFrontToTargetAngle < -PI)
		botFrontToTargetAngle += 2 * PI;
	if (botFrontToTargetAngle > PI)
		botFrontToTargetAngle -= 2 * PI;

	// Decide which way to steer in order to get to the ball.
	if (botFrontToTargetAngle > 0)
		controller.steer = 1;
	else
		controller.steer = -1;

	controller.throttle = 1.1f;

	return controller;
}
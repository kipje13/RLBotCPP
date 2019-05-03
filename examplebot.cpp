#include "examplebot.h"

#include <math.h>
#include <string>

#include "bot.h"
#include "interface.h"
#include "namedrenderer.h"
#include "rlbot_generated.h"

#define PI 3.1415

ExampleBot::ExampleBot(int _index, int _team, std::string _name) : Bot(_index, _team, _name)
{
	
}

Controller ExampleBot::GetOutput(const rlbot::flat::GameTickPacket * gameTickPacket, const rlbot::flat::FieldInfo* fieldInfo)
{
	Controller controller{ 0 };

	rlbot::flat::Vector3 ballLocation = *gameTickPacket->ball()->physics()->location();
	rlbot::flat::Vector3 ballVelocity = *gameTickPacket->ball()->physics()->velocity();
	rlbot::flat::Vector3 carLocation = *gameTickPacket->players()->Get(index)->physics()->location();
	rlbot::flat::Rotator carRotation = *gameTickPacket->players()->Get(index)->physics()->rotation();

	float velocity = sqrt(
		ballVelocity.x() * ballVelocity.x() +
		ballVelocity.y() * ballVelocity.y() + 
		ballVelocity.z() * ballVelocity.z());

	NamedRenderer renderer("test");

	ByteBuffer bytebuffer = Interface::GetBallPrediction();

	auto ballprediction = flatbuffers::GetRoot<rlbot::flat::BallPrediction>(bytebuffer.ptr);

	renderer.StartPacket();

	std::vector<const rlbot::flat::Vector3*> points;

	for (int i = 0; i < ballprediction->slices()->size(); i++)
	{
		points.push_back(ballprediction->slices()->Get(i)->physics()->location());
	}

	renderer.DrawPolyLine3D(Color{ 0xFF, 0x00, 0x00, 0xFF }, points);

	renderer.DrawString2D("Hello world!", Color{ 0x00, 0xFF, 0x00, 0xFF }, rlbot::flat::Vector3{ 10,10,0 }, 4, 4);
	renderer.DrawString3D(std::to_string(velocity), Color{ 0xFF, 0x00, 0xFF, 0xFF }, ballLocation, 2, 2);

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

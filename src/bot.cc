#include "bot.h"

#include <vector>

#include "interface.h"
#include "rlbot_generated.h"

#include "linear_algebra/vec.h"
#include "linear_algebra/mat.h"
#include "linear_algebra/math.h"

Bot::Bot(int _index, int _team, std::string _name) {
  index = _index;
  team = _team;
  name = _name;

  gameInfo = Game(index, team);
}

Input Bot::GetOutput(const rlbot::flat::GameTickPacket* gameTickPacket,
                          const rlbot::flat::FieldInfo* fieldInfo,
                          const rlbot::flat::BallPrediction* ballPrediction) {
  return Input{0};
}

void Bot::SendQuickChat(rlbot::flat::QuickChatSelection message,
                        bool teamOnly) {
  Interface::SendQuickChat(message, index, teamOnly);
}

inline vec3 toVec3(const rlbot::flat::Vector3* v) 
{
	return vec3{v->x(), v->y(), v->z()};
}

inline mat3 toMat3(const rlbot::flat::Rotator* r)
{
	return euler_to_rotation(vec3{ r->pitch(), r->yaw(), r->roll() });
}

void Bot::ReadGameTickPacket(const rlbot::flat::GameTickPacket * gameTickPacket)
{
	gameInfo.frame_delta = gameInfo.time - gameTickPacket->gameInfo()->secondsElapsed();
	gameInfo.time = gameTickPacket->gameInfo()->secondsElapsed();
	gameInfo.time_remaining = gameTickPacket->gameInfo()->gameTimeRemaining();
	
	gameInfo.kickoff_pause = gameTickPacket->gameInfo()->isKickoffPause();
	gameInfo.match_ended = gameTickPacket->gameInfo()->isMatchEnded();
	gameInfo.overtime = gameTickPacket->gameInfo()->isOvertime();
	gameInfo.round_active = gameTickPacket->gameInfo()->isRoundActive();

	gameInfo.gravity = gameTickPacket->gameInfo()->worldGravityZ();

	gameInfo.ball.x = toVec3(gameTickPacket->ball()->physics()->location());
	gameInfo.ball.v = toVec3(gameTickPacket->ball()->physics()->velocity());
	gameInfo.ball.w = toVec3(gameTickPacket->ball()->physics()->angularVelocity());

	gameInfo.ball.time = gameInfo.time;

	gameInfo.num_cars = gameTickPacket->players()->size();

	for (int i = 0; i < gameInfo.num_cars; i++)
	{
		gameInfo.cars[i].x = toVec3(gameTickPacket->players()->Get(i)->physics()->location());
		gameInfo.cars[i].v = toVec3(gameTickPacket->players()->Get(i)->physics()->velocity());
		gameInfo.cars[i].w = toVec3(gameTickPacket->players()->Get(i)->physics()->angularVelocity());
		gameInfo.cars[i].o = toMat3(gameTickPacket->players()->Get(i)->physics()->rotation());

		gameInfo.cars[i].time = gameInfo.time;

		gameInfo.cars[i].jumped = gameTickPacket->players()->Get(i)->jumped();
		gameInfo.cars[i].double_jumped = gameTickPacket->players()->Get(i)->doubleJumped();
		gameInfo.cars[i].on_ground = gameTickPacket->players()->Get(i)->hasWheelContact();
		gameInfo.cars[i].supersonic = gameTickPacket->players()->Get(i)->isSupersonic();
		
		gameInfo.cars[i].boost = gameTickPacket->players()->Get(i)->boost();

		gameInfo.cars[i].id = i;
		gameInfo.cars[i].team = gameTickPacket->players()->Get(i)->team();
	}
}


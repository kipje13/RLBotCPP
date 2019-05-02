#include "bot.h"

#include <stdint.h>

Bot::Bot(int _index, int _team, std::string _name)
{
	index = _index;
	team = _team;
	name = _name;
}

Controller Bot::GetOutput(const rlbot::flat::GameTickPacket * gameTickPacket)
{
	return Controller{ 0 };
}



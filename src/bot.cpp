#include "bot.h"

#include <vector>

#include "interface.h"
#include "rlbot_generated.h"

Bot::Bot(int _index, int _team, std::string _name)
{
	index = _index;
	team = _team;
	name = _name;
}

Controller Bot::GetOutput(const rlbot::flat::GameTickPacket* gameTickPacket, const rlbot::flat::FieldInfo* fieldInfo)
{
	return Controller{ 0 };
}



#pragma once
#include "rlbot_generated.h"
#include "interface.h"

#include <string>

class Bot {
public:
	int index;
	int team;
	std::string name;

	Bot(int index, int team, std::string name);
	virtual Controller GetOutput(const rlbot::flat::GameTickPacket* gameTickPacket);
	const rlbot::flat::FieldInfo* GetFieldInfo();
};
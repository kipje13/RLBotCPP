#include "rlbot_generated.h"

#include "examplebot.h"

#include "bot.h"
#include "botmanager.h"
#include "interface.h"

#ifdef _WIN64
	#define DLLNAME "RLBot_Core_Interface.dll"
#endif

#ifdef _WIN32
	#ifndef _WIN64
		#define DLLNAME "RLBot_Core_Interface_32.dll"
	#endif
#endif

int main(int argc, char** argv)
{
	int botIndex = 0;
	int botTeam = 0;
	std::string botName = "";

	Interface::LoadInterface(DLLNAME);

	while (!Interface::IsInitialized())
	{

	}

	Bot* examplebot = &(ExampleBot(botIndex, botTeam, botName));

	BotManager::RunSingleBot(examplebot);
	
	return 0;
}
#include "rlbot_generated.h"

#include "examplebot.h"

#include "bot.h"
#include "botmanager.h"
#include "interface.h"

#include <windows.h>

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

	Interface::Init(DLLNAME);

	while (!Interface::IsInitialized())
	{

	}

	Bot* examplebot = &(ExampleBot(botIndex, 0, ""));

	BotManager::RunSingleBot(examplebot);
	
	return 0;
}
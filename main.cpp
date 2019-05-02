#include "rlbot_generated.h"

#include "examplebot.h"

#include "bot.h"
#include "interface.h"

#include <windows.h>

int main(int argc, char** argv)
{
	Interface::Init("RLBot_Core_Interface_32.dll");

	int botIndex = 0;

	Bot* examplebot = &(ExampleBot(botIndex, 0, ""));

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
			int status = Interface::SetBotInput(examplebot->GetOutput(flatPacket), botIndex);

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
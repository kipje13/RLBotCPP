#include "rlbot_generated.h"

#include "examplebot.h"

#include "bot.h"
#include "interface.h"

#include <windows.h>

int main(int argc, char** argv)
{
	Interface::Init("RLBot_Core_Interface_32.dll");

	int botIndex = 0;

	while (!Interface::IsInitialized())
	{

	}

	Bot* examplebot = &(ExampleBot(botIndex, 0, ""));

	float lasttime = 0;

	while (true)
	{
		ByteBuffer flatbufferData = Interface::UpdateLiveDataPacketFlatbuffer();

		const rlbot::flat::GameTickPacket *gametickpacket = flatbuffers::GetRoot<rlbot::flat::GameTickPacket>(flatbufferData.ptr);

		if (lasttime != gametickpacket->gameInfo()->secondsElapsed())
		{
			ByteBuffer fieldInfoData = Interface::UpdateFieldInfoFlatbuffer();
			ByteBuffer ballPredictionData = Interface::GetBallPrediction();

			const rlbot::flat::FieldInfo *fieldinfo = flatbuffers::GetRoot<rlbot::flat::FieldInfo>(fieldInfoData.ptr);
			const rlbot::flat::BallPrediction *ballprediction = flatbuffers::GetRoot<rlbot::flat::BallPrediction>(ballPredictionData.ptr);

			int status = Interface::SetBotInput(examplebot->GetOutput(gametickpacket, fieldinfo, ballprediction), botIndex);

			Interface::Free(fieldInfoData.ptr);
			Interface::Free(ballPredictionData.ptr);

			lasttime = gametickpacket->gameInfo()->secondsElapsed();
		}
		else
		{
			Sleep(1);
		}

		Interface::Free(flatbufferData.ptr);
	}
	
	return 0;
}
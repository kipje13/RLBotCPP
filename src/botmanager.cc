#include "botmanager.h"

#include "bot.h"

#include <windows.h>

void botThread(Bot* bot);

void BotManager::RunSingleBot(Bot* bot) { botThread(bot); }

Controller convertControls(Input input)
{
	Controller c;

	c.throttle = input.throttle;
	c.steer = input.steer;

	c.pitch = input.pitch;
	c.yaw = input.yaw;
	c.roll = input.roll;

	c.jump = input.jump;
	c.boost = input.jump;
	c.handbrake = input.handbrake;

	return c;
}

void botThread(Bot* bot) {
  float lasttime = 0;

  while (true) {
    ByteBuffer flatbufferData = Interface::UpdateLiveDataPacketFlatbuffer();

    // Don't try to read the packets when they are very small.
    if (flatbufferData.size > 4) {
      const rlbot::flat::GameTickPacket* gametickpacket =
          flatbuffers::GetRoot<rlbot::flat::GameTickPacket>(flatbufferData.ptr);

      // Only run the bot when we recieve a new packet.
      if (lasttime != gametickpacket->gameInfo()->secondsElapsed()) {
        ByteBuffer fieldInfoData = Interface::UpdateFieldInfoFlatbuffer();
        ByteBuffer ballPredictionData = Interface::GetBallPrediction();

        // The fieldinfo or ball prediction might not have been set up by the
        // framework yet.
        if (fieldInfoData.size > 4 && ballPredictionData.size > 4) {
          const rlbot::flat::FieldInfo* fieldinfo =
              flatbuffers::GetRoot<rlbot::flat::FieldInfo>(fieldInfoData.ptr);
          const rlbot::flat::BallPrediction* ballprediction =
              flatbuffers::GetRoot<rlbot::flat::BallPrediction>(
                  ballPredictionData.ptr);

		  bot->ReadGameTickPacket(gametickpacket);
          int status = Interface::SetBotInput(
              convertControls(bot->GetOutput(gametickpacket, fieldinfo, ballprediction)),
              bot->index);

          Interface::Free(fieldInfoData.ptr);
          Interface::Free(ballPredictionData.ptr);
        }

        lasttime = gametickpacket->gameInfo()->secondsElapsed();
      } else {
        Sleep(1);
      }
    } else {
      Sleep(100);
    }

    Interface::Free(flatbufferData.ptr);
  }
}

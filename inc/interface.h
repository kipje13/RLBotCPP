#pragma once
#include "rlbot_generated.h"

#include <string>

struct ByteBuffer {
	void* ptr;
	int32_t size;
};

struct Controller {
	float throttle;
	float steer;
	float pitch;
	float yaw;
	float roll;
	float jump;
	float boost;
	float handbrake;
};

class Interface
{
public:
	static void LoadInterface(std::string dll);
	static bool IsInitialized();
	static void Free(void* ptr);

	static ByteBuffer UpdateLiveDataPacketFlatbuffer();
	static ByteBuffer UpdateFieldInfoFlatbuffer();
	static ByteBuffer GetBallPrediction();

	static int SetBotInput(Controller input, int index);
	static int RenderGroup(void* data, int size);
	static int SendQuickChat(rlbot::flat::QuickChatSelection message, int botIndex, bool teamOnly);
};
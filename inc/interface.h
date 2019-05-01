#pragma once

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
	static void Init(std::string dll);
	static bool IsInitialized();
	static void Free(void* ptr);

	static ByteBuffer UpdateLiveDataPacketFlatbuffer();
	static ByteBuffer UpdateFieldInfoFlatbuffer();
	static ByteBuffer GetBallPrediction();

	static int SetBotInput(Controller input, int index);
	//static int SendQuickChat(int index, bool teamOnly, rlbot::flat::QuickChatSelection message);
};
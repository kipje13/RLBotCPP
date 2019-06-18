#pragma once
#include "rlbot_generated.h"

#include "matchsettings.h"

#include <string>

#ifdef _WIN64
#define DLLNAME "RLBot_Core_Interface.dll"
#else
#ifdef _WIN32
#define DLLNAME "RLBot_Core_Interface_32.dll"
#endif
#endif

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
  bool jump;
  bool boost;
  bool handbrake;
};

class Interface {
 public:
  static void LoadInterface(std::string dll);
  static bool IsInitialized();
  static void Free(void* ptr);

  static ByteBuffer UpdateLiveDataPacketFlatbuffer();
  static ByteBuffer UpdateFieldInfoFlatbuffer();
  static ByteBuffer GetBallPrediction();

  static int SetBotInput(Controller input, int index);
  static int RenderGroup(void* data, int size);
  static int SendQuickChat(rlbot::flat::QuickChatSelection message,
                           int botIndex, bool teamOnly);
  static int SetGameState(void* data, int size);
  static int StartMatch(MatchSettings settings);
};

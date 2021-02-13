#pragma once
#include "rlbot/rlbot_generated.h"

#include "rlbot/controller.h"
#include "rlbot/matchsettings.h"
#include "rlbot/rlbot.h"
#include "rlbot/statesetting.h"

#include <string>

#if defined(OS_DL_WINDOWS) && defined(OS_64)
#define DLLNAME "RLBot_Core_Interface.dll"
#endif

#if defined(OS_DL_WINDOWS) && defined(OS_32)
#define DLLNAME "RLBot_Core_Interface_32.dll"
#endif

#ifdef OS_DL_LINUX
#define DLLNAME "libRLBotInterface.so" 
#endif

namespace rlbot {
struct ByteBuffer {
  void *ptr;
  int32_t size;
};

class Interface {
private:
  static bool isLoaded;

public:
  static void LoadInterface(std::string dll);
  static bool IsInitialized();
  static bool IsInterfaceLoaded();
  static void Free(void *ptr);

  static ByteBuffer UpdateLiveDataPacketFlatbuffer();
  static ByteBuffer UpdateFieldInfoFlatbuffer();
  static ByteBuffer GetBallPrediction();
  static ByteBuffer GetMatchSettings();
  static ByteBuffer ReceiveQuickChat(int botIndex, int teamIndex,
                                     int lastMessageIndex);

  static int SetBotInput(Controller input, int index);
  static int RenderGroup(void *data, flatbuffers::uoffset_t size);
  static int SendQuickChat(rlbot::flat::QuickChatSelection message,
                           int botIndex, bool teamOnly);
  static int SetGameState(GameState state);
  static int StartMatch(MatchSettings settings);
  static int StartTcpCommunication(int port, bool wantsBallPredictions, bool wantsQuickChat, bool wantsGameMessages);
  static bool IsReadyForCommunication();
};
} // namespace rlbot

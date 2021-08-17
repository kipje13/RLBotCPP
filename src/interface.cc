#include "rlbot/interface.h"

#include <flatbuffers/flatbuffers.h>

#include "rlbot/platform.h"
#include "rlbot/rlbot_generated.h"

namespace rlbot {
typedef bool (*BoolFunc)(void);
typedef ByteBuffer (*ByteBufferFunc)(void);
typedef void (*VoidFunc)(void *);
typedef int (*SendPacketFunc)(void *, int);
typedef ByteBuffer (*ReceiveQuickChatFunc)(int, int, int);
typedef int (*CommsFunc)(int, bool, bool, bool);

BoolFunc _isInitialized;
VoidFunc _free;

ByteBufferFunc _updateLiveDataPacketFlatbuffer;
ByteBufferFunc _updateFieldInfoFlatbuffer;
ByteBufferFunc _getBallPrediction;
ByteBufferFunc _getMatchSettings;
ReceiveQuickChatFunc _receiveChat;

SendPacketFunc _updatePlayerInputFlatbuffer;
SendPacketFunc _renderGroup;
SendPacketFunc _sendQuickChat;
SendPacketFunc _setGameState;
SendPacketFunc _startMatchFlatbuffer;
CommsFunc _startTcpCommunication;
BoolFunc _isReadyForCommunication;

bool Interface::isLoaded = false;

void Interface::LoadInterface(std::string dll) {
  platform::ModuleHandle handle = platform::LoadDll(dll.c_str());

  _isInitialized =
      platform::GetFunctionAddress<BoolFunc>(handle, "IsInitialized");
  _free = platform::GetFunctionAddress<VoidFunc>(handle, "Free");

  _updateLiveDataPacketFlatbuffer =
      platform::GetFunctionAddress<ByteBufferFunc>(
          handle, "UpdateLiveDataPacketFlatbuffer");
  _updateFieldInfoFlatbuffer = platform::GetFunctionAddress<ByteBufferFunc>(
      handle, "UpdateFieldInfoFlatbuffer");
  _getBallPrediction =
      platform::GetFunctionAddress<ByteBufferFunc>(handle, "GetBallPrediction");
  _getMatchSettings =
      platform::GetFunctionAddress<ByteBufferFunc>(handle, "GetMatchSettings");
  _receiveChat =
      platform::GetFunctionAddress<ReceiveQuickChatFunc>(handle, "ReceiveChat");

  _updatePlayerInputFlatbuffer = platform::GetFunctionAddress<SendPacketFunc>(
      handle, "UpdatePlayerInputFlatbuffer");
  _renderGroup =
      platform::GetFunctionAddress<SendPacketFunc>(handle, "RenderGroup");
  _sendQuickChat =
      platform::GetFunctionAddress<SendPacketFunc>(handle, "SendQuickChat");
  _setGameState =
      platform::GetFunctionAddress<SendPacketFunc>(handle, "SetGameState");
  _startMatchFlatbuffer = platform::GetFunctionAddress<SendPacketFunc>(
      handle, "StartMatchFlatbuffer");
  _startTcpCommunication = platform::GetFunctionAddress<CommsFunc>(
          handle, "StartTcpCommunication");
  _isReadyForCommunication = platform::GetFunctionAddress<BoolFunc>(
          handle, "IsReadyForCommunication");

  isLoaded = true;
}

bool Interface::IsInitialized() { return _isInitialized(); }

bool Interface::IsInterfaceLoaded() { return isLoaded; }

void Interface::Free(void *ptr) { _free(ptr); }

ByteBuffer Interface::UpdateLiveDataPacketFlatbuffer() {
  return _updateLiveDataPacketFlatbuffer();
}

ByteBuffer Interface::UpdateFieldInfoFlatbuffer() {
  return _updateFieldInfoFlatbuffer();
}

ByteBuffer Interface::GetBallPrediction() { return _getBallPrediction(); }

ByteBuffer Interface::GetMatchSettings() { return _getMatchSettings(); }

ByteBuffer Interface::ReceiveQuickChat(int botIndex, int teamIndex,
                                       int lastMessageIndex) {
  return _receiveChat(botIndex, teamIndex, lastMessageIndex);
}

int Interface::SetBotInput(Controller input, int index) {
  flatbuffers::FlatBufferBuilder builder(50);

  auto controllerStateOffset = rlbot::flat::CreateControllerState(
      builder, input.throttle, input.steer, input.pitch, input.yaw, input.roll,
      input.jump, input.boost, input.handbrake, input.useItem);

  auto playerInputOffset =
      rlbot::flat::CreatePlayerInput(builder, index, controllerStateOffset);

  builder.Finish(playerInputOffset);

  return _updatePlayerInputFlatbuffer(builder.GetBufferPointer(),
                                      builder.GetSize());
}

int Interface::RenderGroup(void *data, flatbuffers::uoffset_t size) {
  return _renderGroup(data, size);
}

int Interface::SendQuickChat(rlbot::flat::QuickChatSelection message,
                             int botIndex, bool teamOnly) {
  flatbuffers::FlatBufferBuilder builder(50);

  auto quickChatOffset =
      rlbot::flat::CreateQuickChat(builder, message, botIndex, teamOnly);
  builder.Finish(quickChatOffset);

  return _sendQuickChat(builder.GetBufferPointer(), builder.GetSize());
}

int Interface::SetGameState(GameState state) {
  flatbuffers::FlatBufferBuilder builder(1000);
  builder.Finish(state.BuildFlatBuffer(builder));

  return _setGameState(builder.GetBufferPointer(), builder.GetSize());
}

int Interface::StartMatch(MatchSettings settings) {
  flatbuffers::FlatBufferBuilder builder(1000);
  builder.Finish(settings.BuildFlatBuffer(builder));

  return _startMatchFlatbuffer(builder.GetBufferPointer(), builder.GetSize());
}

int Interface::StartTcpCommunication(int port, bool wantsBallPredictions, bool wantsQuickChat, bool wantsGameMessages) {
    return _startTcpCommunication(port, wantsBallPredictions, wantsQuickChat, wantsGameMessages);
}

bool Interface::IsReadyForCommunication() {
    return _isReadyForCommunication();
}
} // namespace rlbot

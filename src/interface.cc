#include "interface.h"

#include "platform.h"

#include "flatbuffers/flatbuffers.h"
#include "rlbot_generated.h"

namespace rlbot {
typedef bool (*BoolFunc)(void);
typedef ByteBuffer (*ByteBufferFunc)(void);
typedef void (*VoidFunc)(void *);
typedef int (*SendPacketFunc)(void *, int);
typedef ByteBuffer (*ReceiveQuickChatFunc)(int, int, int);

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

void Interface::LoadInterface(std::string dll) {
  platform::ModuleHandle handle = platform::LoadDll(dll.c_str());

  _isInitialized =
      (BoolFunc)platform::GetFunctionAddress(handle, "IsInitialized");
  _free = (VoidFunc)platform::GetFunctionAddress(handle, "Free");

  _updateLiveDataPacketFlatbuffer =
      (ByteBufferFunc)platform::GetFunctionAddress(
          handle, "UpdateLiveDataPacketFlatbuffer");
  _updateFieldInfoFlatbuffer = (ByteBufferFunc)platform::GetFunctionAddress(
      handle, "UpdateFieldInfoFlatbuffer");
  _getBallPrediction =
      (ByteBufferFunc)platform::GetFunctionAddress(handle, "GetBallPrediction");
  _getMatchSettings =
      (ByteBufferFunc)platform::GetFunctionAddress(handle, "GetMatchSettings");
  _receiveChat =
      (ReceiveQuickChatFunc)platform::GetFunctionAddress(handle, "ReceiveChat");

  _updatePlayerInputFlatbuffer = (SendPacketFunc)platform::GetFunctionAddress(
      handle, "UpdatePlayerInputFlatbuffer");
  _renderGroup =
      (SendPacketFunc)platform::GetFunctionAddress(handle, "RenderGroup");
  _sendQuickChat =
      (SendPacketFunc)platform::GetFunctionAddress(handle, "SendQuickChat");
  _setGameState =
      (SendPacketFunc)platform::GetFunctionAddress(handle, "SetGameState");
  _startMatchFlatbuffer = (SendPacketFunc)platform::GetFunctionAddress(
      handle, "StartMatchFlatbuffer");
}

bool Interface::IsInitialized() { return _isInitialized(); }

void Interface::Free(void *ptr) { _free(ptr); }

ByteBuffer Interface::UpdateLiveDataPacketFlatbuffer() {
  return _updateLiveDataPacketFlatbuffer();
}

ByteBuffer Interface::UpdateFieldInfoFlatbuffer() {
  return _updateFieldInfoFlatbuffer();
}

ByteBuffer Interface::GetBallPrediction() { return _getBallPrediction(); }

ByteBuffer Interface::GetMatchSettings() { return _getMatchSettings(); }

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
} // namespace rlbot

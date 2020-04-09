#pragma once

#include "rlbot/flatbuffercontainer.h"

namespace rlbot {
typedef FlatbufferContainer<rlbot::flat::GameTickPacket> GameTickPacket;
typedef FlatbufferContainer<rlbot::flat::BallPrediction> BallPrediction;
typedef FlatbufferContainer<rlbot::flat::FieldInfo> FieldInfo;
typedef FlatbufferContainer<rlbot::flat::MatchSettings> MatchInfo;
typedef FlatbufferContainer<rlbot::flat::QuickChatMessages> QuickChatMessages;
} // namespace rlbot

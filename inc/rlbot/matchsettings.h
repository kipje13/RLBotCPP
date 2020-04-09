#pragma once

#include <flatbuffers/flatbuffers.h>

#include "rlbot/rlbot_generated.h"

#include <string>
#include <vector>

namespace rlbot {
class MutatorSettings {
public:
  rlbot::flat::MatchLength matchLength = rlbot::flat::MatchLength_Five_Minutes;
  rlbot::flat::MaxScore maxScore = rlbot::flat::MaxScore_Unlimited;
  rlbot::flat::OvertimeOption overtime = rlbot::flat::OvertimeOption_Unlimited;
  rlbot::flat::SeriesLengthOption seriesLength =
      rlbot::flat::SeriesLengthOption_Unlimited;
  rlbot::flat::GameSpeedOption gameSpeed = rlbot::flat::GameSpeedOption_Default;
  rlbot::flat::BallMaxSpeedOption ballMaxSpeed =
      rlbot::flat::BallMaxSpeedOption_Default;
  rlbot::flat::BallTypeOption ballType = rlbot::flat::BallTypeOption_Default;
  rlbot::flat::BallWeightOption ballWeight =
      rlbot::flat::BallWeightOption_Default;
  rlbot::flat::BallSizeOption ballSize = rlbot::flat::BallSizeOption_Default;
  rlbot::flat::BallBouncinessOption ballBounciness =
      rlbot::flat::BallBouncinessOption_Default;
  rlbot::flat::BoostOption boostOption = rlbot::flat::BoostOption_Normal_Boost;
  rlbot::flat::RumbleOption rumbleOption = rlbot::flat::RumbleOption_Default;
  rlbot::flat::BoostStrengthOption boostStrength =
      rlbot::flat::BoostStrengthOption_One;
  rlbot::flat::GravityOption gravity = rlbot::flat::GravityOption_Default;
  rlbot::flat::DemolishOption demolishOption =
      rlbot::flat::DemolishOption_Default;
  rlbot::flat::RespawnTimeOption respawnTime =
      rlbot::flat::RespawnTimeOption_Three_Seconds;

  flatbuffers::Offset<rlbot::flat::MutatorSettings>
  BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder);
};

class PlayerLoadout {
public:
  int teamColorId = 60;
  int customColorId = 0;
  int carId = 23;
  int carPaintId = 0;
  int decalId = 0;
  int decalPaintId = 0;
  int wheelsId = 1565;
  int wheelsPaintId = 0;
  int boostId = 35;
  int boostPaintId = 0;
  int antennaId = 0;
  int antennaPaintId = 0;
  int hatId = 0;
  int hatPaintId = 0;
  int paintFinishId = 1681;
  int customFinishId = 1681;
  int engineAudioId = 0;
  int trailsId = 3220;
  int trailsPaintId = 0;
  int goalExplosionId = 3018;
  int goalExplosionPaintId = 0;

  flatbuffers::Offset<rlbot::flat::PlayerLoadout>
  BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder);
};

class PlayerConfig {
public:
  std::string name;
  int team = 0;
  float botSkill = 1.0f;
  rlbot::flat::PlayerClass playerType;
  PlayerLoadout loadout;

  flatbuffers::Offset<rlbot::flat::PlayerConfiguration>
  BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder);
};

class MatchSettings {
public:
  std::vector<PlayerConfig> players;
  MutatorSettings mutatorSettings;

  rlbot::flat::GameMode gameMode = rlbot::flat::GameMode_Soccer;
  rlbot::flat::GameMap gameMap = rlbot::flat::GameMap_DFHStadium;
  bool skipReplays = false;
  bool instantStart = false;

  flatbuffers::Offset<rlbot::flat::MatchSettings>
  BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder);
};
} // namespace rlbot

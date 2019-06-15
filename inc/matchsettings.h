#pragma once

#include "flatbuffers/flatbuffers.h"
#include "rlbot_generated.h"

#include <string>
#include <vector>

class MutatorSettings {
public:
  rlbot::flat::MatchLength matchLength;
  rlbot::flat::MaxScore maxScore;
  rlbot::flat::OvertimeOption overtime;
  rlbot::flat::SeriesLengthOption seriesLength;
  rlbot::flat::GameSpeedOption gameSpeed;
  rlbot::flat::BallMaxSpeedOption ballMaxSpeed;
  rlbot::flat::BallTypeOption ballType;
  rlbot::flat::BallWeightOption ballWeight;
  rlbot::flat::BallSizeOption ballSize;
  rlbot::flat::BallBouncinessOption ballBounciness;
  rlbot::flat::BoostOption boostOption;
  rlbot::flat::RumbleOption rumbleOption;
  rlbot::flat::BoostStrengthOption boostStrength;
  rlbot::flat::GravityOption gravity;
  rlbot::flat::DemolishOption demolishOption;
  rlbot::flat::RespawnTimeOption respawnTime;

  MutatorSettings();
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
};

class PlayerConfig {
public:
  std::string name;
  int team = 0;
  float botSkill = 1.0f;
  rlbot::flat::PlayerClass playerType;
  PlayerLoadout loadout;
};

class MatchSettings {
public:
  std::vector<PlayerConfig> players;
  MutatorSettings mutatorSettings;

  rlbot::flat::GameMode gameMode = rlbot::flat::GameMode_Soccer;
  rlbot::flat::GameMap gameMap = rlbot::flat::GameMap_DFHStadium;
  bool skipReplays = false;
  bool instantStart = false;

  void BuildFlatbuffersPacket(flatbuffers::FlatBufferBuilder &builder);
};

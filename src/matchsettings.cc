#include "MatchSettings.h"

#include "flatbuffers/flatbuffers.h"
#include "rlbot_generated.h"

MutatorSettings::MutatorSettings() {
  matchLength = rlbot::flat::MatchLength::MatchLength_Five_Minutes;
  maxScore = rlbot::flat::MaxScore::MaxScore_Unlimited;
  overtime = rlbot::flat::OvertimeOption::OvertimeOption_Unlimited;
  seriesLength = rlbot::flat::SeriesLengthOption::SeriesLengthOption_Unlimited;
  gameSpeed = rlbot::flat::GameSpeedOption::GameSpeedOption_Default;
  ballMaxSpeed = rlbot::flat::BallMaxSpeedOption::BallMaxSpeedOption_Default;
  ballType = rlbot::flat::BallTypeOption::BallTypeOption_Default;
  ballWeight = rlbot::flat::BallWeightOption::BallWeightOption_Default;
  ballSize = rlbot::flat::BallSizeOption::BallSizeOption_Default;
  ballBounciness =
      rlbot::flat::BallBouncinessOption::BallBouncinessOption_Default;
  boostOption = rlbot::flat::BoostOption::BoostOption_Normal_Boost;
  rumbleOption = rlbot::flat::RumbleOption::RumbleOption_Default;
  boostStrength = rlbot::flat::BoostStrengthOption::BoostStrengthOption_One;
  gravity = rlbot::flat::GravityOption::GravityOption_Default;
  demolishOption = rlbot::flat::DemolishOption::DemolishOption_Default;
  respawnTime = rlbot::flat::RespawnTimeOption::RespawnTimeOption_Three_Seconds;
}

void MatchSettings::BuildFlatbuffersPacket(
    flatbuffers::FlatBufferBuilder &builder) {
  auto mutatorOffset = rlbot::flat::CreateMutatorSettings(
      builder, mutatorSettings.matchLength, mutatorSettings.maxScore,
      mutatorSettings.overtime, mutatorSettings.seriesLength,
      mutatorSettings.gameSpeed, mutatorSettings.ballMaxSpeed,
      mutatorSettings.ballType, mutatorSettings.ballWeight,
      mutatorSettings.ballSize, mutatorSettings.ballBounciness,
      mutatorSettings.boostOption, mutatorSettings.rumbleOption,
      mutatorSettings.boostStrength, mutatorSettings.gravity,
      mutatorSettings.demolishOption, mutatorSettings.respawnTime);

  std::vector<flatbuffers::Offset<rlbot::flat::PlayerConfiguration>>
      playerOffsets;

  for (int i = 0; i < players.size(); i++) {
    PlayerLoadout loadout = players[i].loadout;

    auto nameOffset = builder.CreateString(players[i].name.c_str());

    auto paintOffset = rlbot::flat::CreateLoadoutPaint(
        builder, loadout.carPaintId, loadout.decalPaintId,
        loadout.wheelsPaintId, loadout.boostPaintId, loadout.antennaPaintId,
        loadout.hatPaintId, loadout.trailsPaintId, loadout.goalExplosionId);

    auto loadoutOffset = rlbot::flat::CreatePlayerLoadout(
        builder, loadout.teamColorId, loadout.customColorId, loadout.carId,
        loadout.decalId, loadout.wheelsId, loadout.boostId, loadout.antennaId,
        loadout.hatId, loadout.paintFinishId, loadout.customFinishId,
        loadout.engineAudioId, loadout.trailsId, loadout.goalExplosionId,
        paintOffset);

    flatbuffers::Offset<void> playerClass;

    switch (players[i].playerType) {
    case rlbot::flat::PlayerClass_HumanPlayer:
      playerClass = rlbot::flat::CreateHumanPlayer(builder).Union();
      break;

    case rlbot::flat::PlayerClass_PartyMemberBotPlayer:
      playerClass = rlbot::flat::CreatePartyMemberBotPlayer(builder).Union();
      break;

    case rlbot::flat::PlayerClass_PsyonixBotPlayer:
      playerClass =
          rlbot::flat::CreatePsyonixBotPlayer(builder, players[i].botSkill)
              .Union();
      break;

    case rlbot::flat::PlayerClass_RLBotPlayer:
      playerClass = rlbot::flat::CreateRLBotPlayer(builder).Union();
      break;
    }

    playerOffsets.push_back(rlbot::flat::CreatePlayerConfiguration(
        builder, players[i].playerType, playerClass, nameOffset,
        players[i].team, loadoutOffset));
  }

  auto playerVector = builder.CreateVector(playerOffsets);

  auto matchSettingsOffset = rlbot::flat::CreateMatchSettings(
      builder, playerVector, gameMode, gameMap, skipReplays, instantStart,
      mutatorOffset);
  builder.Finish(matchSettingsOffset);
}

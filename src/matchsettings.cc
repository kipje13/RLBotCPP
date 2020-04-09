#include "rlbot/matchsettings.h"

#include <flatbuffers/flatbuffers.h>

#include "rlbot/rlbot_generated.h"

namespace rlbot {
flatbuffers::Offset<rlbot::flat::MutatorSettings>
MutatorSettings::BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder) {
  auto mutatorOffset = rlbot::flat::CreateMutatorSettings(
      builder, matchLength, maxScore, overtime, seriesLength, gameSpeed,
      ballMaxSpeed, ballType, ballWeight, ballSize, ballBounciness, boostOption,
      rumbleOption, boostStrength, gravity, demolishOption, respawnTime);

  return mutatorOffset;
}

flatbuffers::Offset<rlbot::flat::PlayerLoadout>
PlayerLoadout::BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder) {
  auto paintOffset = rlbot::flat::CreateLoadoutPaint(
      builder, carPaintId, decalPaintId, wheelsPaintId, boostPaintId,
      antennaPaintId, hatPaintId, trailsPaintId, goalExplosionId);

  auto loadoutOffset = rlbot::flat::CreatePlayerLoadout(
      builder, teamColorId, customColorId, carId, decalId, wheelsId, boostId,
      antennaId, hatId, paintFinishId, customFinishId, engineAudioId, trailsId,
      goalExplosionId, paintOffset);

  return loadoutOffset;
}

flatbuffers::Offset<rlbot::flat::PlayerConfiguration>
PlayerConfig::BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder) {
  auto nameOffset = builder.CreateString(name.c_str());

  auto loadoutOffset = loadout.BuildFlatBuffer(builder);

  flatbuffers::Offset<void> playerClass;

  switch (playerType) {
  case rlbot::flat::PlayerClass_HumanPlayer:
    playerClass = rlbot::flat::CreateHumanPlayer(builder).Union();
    break;

  case rlbot::flat::PlayerClass_PartyMemberBotPlayer:
    playerClass = rlbot::flat::CreatePartyMemberBotPlayer(builder).Union();
    break;

  case rlbot::flat::PlayerClass_PsyonixBotPlayer:
    playerClass =
        rlbot::flat::CreatePsyonixBotPlayer(builder, botSkill).Union();
    break;

  case rlbot::flat::PlayerClass_RLBotPlayer:
    playerClass = rlbot::flat::CreateRLBotPlayer(builder).Union();
    break;
  }

  auto playerconfig = rlbot::flat::CreatePlayerConfiguration(
      builder, playerType, playerClass, nameOffset, team, loadoutOffset);

  return playerconfig;
}

flatbuffers::Offset<rlbot::flat::MatchSettings>
MatchSettings::BuildFlatBuffer(flatbuffers::FlatBufferBuilder &builder) {
  auto mutatorOffset = mutatorSettings.BuildFlatBuffer(builder);

  std::vector<flatbuffers::Offset<rlbot::flat::PlayerConfiguration>>
      playerOffsets;

  for (int i = 0; i < players.size(); i++) {
    playerOffsets.push_back(players[i].BuildFlatBuffer(builder));
  }

  auto playerVector = builder.CreateVector(playerOffsets);

  auto matchSettingsOffset = rlbot::flat::CreateMatchSettings(
      builder, playerVector, gameMode, gameMap, skipReplays, instantStart,
      mutatorOffset);

  return matchSettingsOffset;
}
} // namespace rlbot

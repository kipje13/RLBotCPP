#pragma once

#include "rlbot/bot.h"
#include "rlbot/botprocess.h"
#include "rlbot/platform.h"
#include "rlbot/server.h"

#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace rlbot {
class BotManager {
private:
  std::map<int, std::unique_ptr<BotProcess>> bots;
  std::mutex bots_mutex;

  Bot *(*botfactory)(int, int, std::string);

public:
  BotManager(BotManager const &) = delete;
  BotManager &operator=(BotManager const &) = delete;

  BotManager(Bot *(*botfactory)(int, int, std::string));

  /*void RunSingleBot(int index, int team, std::string name) {
    BotThread(InstantiateBot(index, team, name));
  }*/

  void StartBotServer(uint16_t port);
  void RecieveMessage(Message message);
  void AddBot(int index, int team, std::string name);
  void RemoveBot(int index);
};
} // namespace rlbot

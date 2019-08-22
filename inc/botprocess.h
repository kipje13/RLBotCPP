#pragma once

#include "bot.h"
#include <thread>

namespace rlbot {
class BotProcess {
private:
  Bot *bot;
  bool running = false;
  std::thread thread;

public:
  BotProcess(BotProcess const &) = delete;
  BotProcess &operator=(BotProcess const &) = delete;

  BotProcess(Bot *b) { bot = b; }
  ~BotProcess() { delete bot; }

  void Start();
  void Stop();
  void BotThread();
};
} // namespace rlbot

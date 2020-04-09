#pragma once

#include "rlbot/bot.h"

#include <thread>

namespace rlbot {
class BotProcess {
private:
  Bot *bot;
  bool running = false;
  std::thread thread;

  void BotThread() const;

public:
  BotProcess(BotProcess const &) = delete;
  BotProcess &operator=(BotProcess const &) = delete;

  /**
   * Instantiates a bot process.
   * @param b the bot instance for this process.
   */
  BotProcess(Bot *b) { bot = b; }
  ~BotProcess() { delete bot; }

  /**
   * Starts execution of the bot assosiated with this process.
   */
  void Start();

  /**
   * Stops execution of the bot assosiated with this process.
   */
  void Stop();
};
} // namespace rlbot

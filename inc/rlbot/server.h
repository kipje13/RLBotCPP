#pragma once

#include <cstdint>
#include <functional>
#include <string>

namespace rlbot {
enum Command { Add, Remove };

struct Message {
  Command command;
  int index;
  int team;
  std::string name;
  std::string dll_dir;
};

class Server {
private:
  static bool isInitialized;

public:
  static void Run(uint16_t port, std::function<void(Message)> callback);
};
} // namespace rlbot

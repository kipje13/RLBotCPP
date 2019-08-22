#pragma once

#include "bot.h"
#include "botprocess.h"

#include "platform.h"
#include "server.h"

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
template <typename T> class BotManager {
private:
  std::map<int, std::unique_ptr<BotProcess>> bots;
  std::mutex bots_mutex;

public:
  BotManager(BotManager const &) = delete;
  BotManager &operator=(BotManager const &) = delete;
  BotManager(){};

  /*void RunSingleBot(int index, int team, std::string name) {
    BotThread(InstantiateBot(index, team, name));
  }*/

  void StartBotServer(uint16_t port) {
    using namespace std::placeholders;

    std::cout << "Started listening on port: " << port << std::endl;
    std::thread tcpserver(Server::Run, port,
                          std::bind(&BotManager::RecieveMessage, this, _1));
    tcpserver.join();
  }

  void RecieveMessage(Message message) {
    if (message.command == Command::Add) {
      if (!Interface::IsInterfaceLoaded()) {
        Interface::LoadInterface(message.dll_dir + "\\" + DLLNAME);
      }
      AddBot(message.index, message.team, message.name);
    } else if (message.command == Command::Remove) {
      RemoveBot(message.index);
    }
  }

  void AddBot(int index, int team, std::string name) {
    bots_mutex.lock();

    if (bots.find(index) == bots.end()) {
      bots.insert(std::make_pair(
          index,
          std::make_unique<BotProcess>(InstantiateBot(index, team, name))));

      bots[index]->Start();

      std::cout << "Spawning bot \"" << name << "\" with index " << index
                << std::endl;
    }

    bots_mutex.unlock();
  }

  void RemoveBot(int index) {
    bots_mutex.lock();

    if (bots.find(index) != bots.end()) {
      bots[index]->Stop();
      bots.erase(index);

      std::cout << "Removed bot with index " << index << std::endl;
    }

    bots_mutex.unlock();
  }

  Bot *InstantiateBot(int index, int team, std::string name) {
    return new T(index, team, name);
  }
};
} // namespace rlbot

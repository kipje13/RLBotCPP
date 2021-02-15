#include "rlbot/botmanager.h"
#include <chrono>
#include <thread>

namespace rlbot {
BotManager::BotManager(Bot *(*botfactory)(int, int, std::string)) {
  this->botfactory = botfactory;
}

void BotManager::StartBotServer(uint16_t port) {
  using namespace std::placeholders;

  std::cout << "Started listening on port: " << port << std::endl;
  std::thread tcpserver(Server::Run, port,
                        std::bind(&BotManager::RecieveMessage, this, _1));                        
  tcpserver.join();
}

void BotManager::RecieveMessage(Message message) {
  using namespace std::chrono_literals;
  if (message.command == Command::Add) {
    if (!Interface::IsInterfaceLoaded()) {
      Interface::LoadInterface(message.dll_dir + platform::fileSeperator +
                               DLLNAME);
      Interface::StartTcpCommunication(23234, true, true, true);
      std::cout << "CPP bot manager waiting for the interface to connect..." << std::endl;
      while (!Interface::IsReadyForCommunication()) {
        std::this_thread::sleep_for(50ms);
      }
    }
    AddBot(message.index, message.team, message.name);
  } else if (message.command == Command::Remove) {
    RemoveBot(message.index);
  }
}

void BotManager::AddBot(int index, int team, std::string name) {
  bots_mutex.lock();

  if (bots.find(index) == bots.end()) {
    bots.insert(std::make_pair(
        index, std::make_unique<BotProcess>(botfactory(index, team, name))));

    bots[index]->Start();

    std::cout << "Spawning bot \"" << name << "\" with index " << index
              << std::endl;
  }

  bots_mutex.unlock();
}

void BotManager::RemoveBot(int index) {
  bots_mutex.lock();

  if (bots.find(index) != bots.end()) {
    bots[index]->Stop();
    bots.erase(index);

    std::cout << "Removed bot with index " << index << std::endl;
  }

  bots_mutex.unlock();
}
} // namespace rlbot

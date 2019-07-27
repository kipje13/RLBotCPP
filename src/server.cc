#include "server.h"

#include "sockets.h"

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string string, char seperator) {
  size_t pos = 0;
  std::vector<std::string> substrings;

  while ((pos = string.find(seperator)) != std::string::npos) {
    substrings.push_back(string.substr(0, pos));
    string.erase(0, pos + 1);
  }

  substrings.push_back(string);

  return substrings;
}

bool isNumber(std::string string) {
  for (int i = 0; i < string.length(); i++) {
    if (!std::isdigit(string[i]))
      return false;
  }

  return true;
}

bool Server::isInitialized = false;

void Server::Run(uint16_t port, std::function<void(Message)> callback) {
  if (!isInitialized)
    Sockets::Initialize();

  Sockets::ListenSocket server = Sockets::ListenSocketCreate(port);
  Sockets::ListenSocketStart(server);

  while (true) {
    Sockets::Socket client = Sockets::ListenSocketAccept(server);
    std::string message = Sockets::SocketRecieveString(client);

    std::vector<std::string> params = split(message, '\n');

    Message m;

    if (params[0] == "add") {
      m.command = Command::Add;

      if (isNumber(params[2])) {
        m.index = std::stoi(params[2]);
      } else {
        std::cerr << "Invalid tcp message!" << std::endl;
        continue;
      }

      if (isNumber(params[3])) {
        m.team = std::stoi(params[3]);
      } else {
        std::cerr << "Invalid tcp message!" << std::endl;
        continue;
      }

      m.name = params[1];
      m.dll_dir = params[4];
    } else if (params[0] == "remove") {
      m.command = Command::Remove;

      if (isNumber(params[1])) {
        m.index = std::stoi(params[1]);
      } else {
        std::cerr << "Invalid tcp message!" << std::endl;
        continue;
      }
    } else {
      std::cerr << "Invalid tcp command!" << std::endl;
      continue;
    }

    callback(m);
  }
}

#pragma once

#include <cstdint>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET socket_t;
#endif

namespace rlbotcpp {
namespace sockets {

struct ListenSocket {
  socket_t internal_socket;
};

struct Socket {
  socket_t internal_socket;
};

void Initialize();

ListenSocket ListenSocketCreate(uint16_t port);
void ListenSocketClose(ListenSocket listenSocket);
void ListenSocketStart(ListenSocket listenSocket);
Socket ListenSocketAccept(ListenSocket listenSocket);

std::string SocketRecieveString(Socket socket);
void SocketClose(Socket socket);
} // namespace sockets
} // namespace rlbotcpp

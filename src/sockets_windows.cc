#include "rlbot/sockets.h"

#ifdef OS_WINDOWS
#include "stdio.h"

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace rlbot {
namespace sockets {
void Initialize() {
  WORD wVersionRequested = MAKEWORD(2, 2);
  WSADATA wsaData;

  int err = WSAStartup(wVersionRequested, &wsaData);
  if (err != 0) {
    printf("WSAStartup failed with error: %d\n", err);
    return;
  }
}

ListenSocket ListenSocketCreate(uint16_t port) {
  // Convert port to string
  std::string portstring = std::to_string(port);

  struct addrinfo *result = NULL, hints;

  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  // Resolve the local address and port to be used by the server
  int iResult = getaddrinfo(NULL, portstring.c_str(), &hints, &result);
  if (iResult != 0) {
    printf("getaddrinfo failed: %d\n", iResult);
    return ListenSocket{};
  }

  SOCKET listenSocket = INVALID_SOCKET;
  listenSocket =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);

  if (listenSocket == INVALID_SOCKET) {
    printf("Error at socket(): %ld\n", WSAGetLastError());
    freeaddrinfo(result);
    return ListenSocket{};
  }

  iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
  if (iResult == SOCKET_ERROR) {
    printf("bind failed with error: %d\n", WSAGetLastError());
    freeaddrinfo(result);
    return ListenSocket{};
  }

  freeaddrinfo(result);

  ListenSocket socket;
  socket.internal_socket = listenSocket;

  return socket;
}

void ListenSocketStart(ListenSocket listenSocket) {
  if (listen(listenSocket.internal_socket, SOMAXCONN) == SOCKET_ERROR) {
    printf("Listen failed with error: %ld\n", WSAGetLastError());
    return;
  }
}

Socket ListenSocketAccept(ListenSocket listenSocket) {
  SOCKET clientSocket = accept(listenSocket.internal_socket, NULL, NULL);
  if (clientSocket == INVALID_SOCKET) {
    printf("accept failed: %d\n", WSAGetLastError());
    return Socket{};
  }

  Socket socket;
  socket.internal_socket = clientSocket;

  return socket;
}

void ListenSocketClose(ListenSocket listenSocket) {
  closesocket(listenSocket.internal_socket);
}

std::string SocketRecieveString(Socket socket) {
  char receivebuffer[0xFFFF];
  int size =
      recv(socket.internal_socket, receivebuffer, sizeof(receivebuffer), NULL);

  if (size == SOCKET_ERROR) {
    printf("Socket recieving failed: %d\n", WSAGetLastError());
    return std::string();
  }

  std::string message(receivebuffer, size);

  return message;
}

void SocketClose(Socket socket) { closesocket(socket.internal_socket); }
} // namespace sockets
} // namespace rlbot
#endif
#include "sockets.h"

#ifdef __linux__
#include "stdio.h"

namespace rlbot {
namespace sockets {
void Initialize() {
  
}

ListenSocket ListenSocketCreate(uint16_t port) {
  // Convert port to string
  std::string portstring = std::to_string(port);



  ListenSocket socket;
  socket.internal_socket = listenSocket;

  return socket;
}

void ListenSocketStart(ListenSocket listenSocket) {

}

Socket ListenSocketAccept(ListenSocket listenSocket) {
  

  Socket socket;
  socket.internal_socket = clientSocket;

  return socket;
}

void ListenSocketClose(ListenSocket listenSocket) {
  
}

std::string SocketRecieveString(Socket socket) {
  char receivebuffer[0xFFFF];
  

  std::string message(receivebuffer, size);

  return message;
}

void SocketClose(Socket socket) 
{  

}
} // namespace sockets
} // namespace rlbot
#endif
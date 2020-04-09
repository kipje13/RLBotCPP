#include "rlbot/sockets.h"

#ifdef OS_UNIX
#include "stdio.h"

#include <iostream>

#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 

namespace rlbot {
namespace sockets {
void Initialize() {
  
}

ListenSocket ListenSocketCreate(uint16_t port) {

  int server;
  struct sockaddr_in address; 
  int opt = 1; 

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
  { 
    printf("Creating socket failed.\n"); 
    return ListenSocket{};
  } 

  if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) 
  { 
    printf("setsockopt failed.\n"); 
    return ListenSocket{};
  } 

  address.sin_family = AF_INET; 
  address.sin_addr.s_addr = INADDR_ANY; 
  address.sin_port = htons( port );

  if (bind(server, (struct sockaddr *)&address, sizeof(address)) < 0) 
  { 
    printf("bind failed.\n"); 
    return ListenSocket{};
  } 

  ListenSocket socket;
  socket.internal_socket = server;

  return socket;
}

void ListenSocketStart(ListenSocket listenSocket) {
  if (listen(listenSocket.internal_socket, 10) < 0) 
  { 
    printf("listen failed.\n"); 
    return;
  } 
}

Socket ListenSocketAccept(ListenSocket listenSocket) {
  socket_t client_socket = accept(listenSocket.internal_socket, NULL, NULL);
  if (client_socket < 0)
  { 
    printf("accept failed.\n"); 
    return Socket{};
  }

  Socket socket;
  socket.internal_socket = client_socket;

  return socket;
}

void ListenSocketClose(ListenSocket listenSocket) {
  close(listenSocket.internal_socket);
}

std::string SocketRecieveString(Socket socket) {
  char receivebuffer[0xFFFF];
  
  ssize_t size = read( socket.internal_socket , receivebuffer, sizeof(receivebuffer)); 
  std::string message(receivebuffer, size);

  return message;
}

void SocketClose(Socket socket) {  
  close(socket.internal_socket);
}
} // namespace sockets
} // namespace rlbot
#endif
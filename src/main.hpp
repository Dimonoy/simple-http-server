#ifndef _MAIN_HPP
#define _MAIN_HPP 1

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace msrv {

typedef struct m_socket {
  int fd = -1;
  uint8_t domain;
  uint8_t type;
  uint8_t protocol = 0;
} m_socket;

void call_error(const std::string& msg);

class Server {
private:
  m_socket sock;
  int port = 8080;
  struct sockaddr_in sock_addr;
  int binding_status = -1;
  int listener_status = -1;

public:
  int get_sock_fd();
  int get_binding_status();
  int get_listener_status();
  struct sockaddr_in* get_sock_addr();

  void set_sock(m_socket sock);
  void set_sock_addr(struct sockaddr_in sock_addr);
  void set_binding_status(int binding_status);
  void set_listener_status(int listener_status);

  void accept_client();
  void close_sock();
};

class ServerBuilder {
private:
  Server* server;
public:
  ServerBuilder();
  ~ServerBuilder();
  void reset_server();

  void build_sock(uint8_t domain, uint8_t type);
  void build_binding(sa_family_t sin_family, in_port_t port, in_addr_t addr);
  void build_listener(uint8_t n_to_listen);

  Server* get_server();
};

class ServerDirector {
public:
  void setup_server(ServerBuilder* server_builder);
};

} // namespace msrv

#endif // _MAIN_HPP

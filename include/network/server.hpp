#ifndef NETWORK_SERVER_HPP
#define NETWORK_SERVER_HPP

#include <netinet/in.h>
#include <unistd.h>

namespace msrv {

typedef struct m_socket {
  int fd = -1;
  uint8_t domain;
  uint8_t type;
  uint8_t protocol = 0;
} m_socket;

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
  struct sockaddr_in *get_sock_addr();

  void set_sock(m_socket sock);
  void set_sock_addr(struct sockaddr_in sock_addr);
  void set_binding_status(int binding_status);
  void set_listener_status(int listener_status);

  void accept_client();
  void close_sock();
};

} // namespace msrv

#endif // NETWORK_SERVER_HPP

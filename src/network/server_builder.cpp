#include "utils/error.hpp"

#include "network/server_builder.hpp"

msrv::ServerBuilder::ServerBuilder() { this->reset_server(); }

msrv::ServerBuilder::~ServerBuilder() { delete server; }

void msrv::ServerBuilder::reset_server() { this->server = new Server(); }

void msrv::ServerBuilder::build_sock(uint8_t domain, uint8_t type) {
  m_socket sock;
  sock.domain = domain;
  sock.type = type;
  sock.fd = socket(sock.domain, sock.type, sock.protocol);

  if (sock.fd < 0)
    msrv::call_error("Socket connection failed");

  this->server->set_sock(sock);
}

void msrv::ServerBuilder::build_binding(sa_family_t sin_family, in_port_t port,
                                        in_addr_t addr) {
  struct sockaddr_in sock_addr;
  sock_addr.sin_family = sin_family;
  sock_addr.sin_port = port;
  sock_addr.sin_addr.s_addr = addr;
  server->set_sock_addr(sock_addr);

  int binding_status = bind(this->server->get_sock_fd(),
                            (struct sockaddr *)&sock_addr, sizeof(sock_addr));
  if (binding_status < 0)
    msrv::call_error("Binding failed");

  this->server->set_binding_status(binding_status);
}

void msrv::ServerBuilder::build_listener(uint8_t n_to_listen) {
  int listener_status = listen(this->server->get_sock_fd(), n_to_listen);
  if (listener_status < 0)
    msrv::call_error("Listening failed");

  this->server->set_listener_status(listener_status);
}

msrv::Server *msrv::ServerBuilder::get_server() {
  Server *server = this->server;
  this->reset_server();

  return server;
}

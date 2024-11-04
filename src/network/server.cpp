#include <sys/socket.h>

#include "network/server.hpp"

int msrv::Server::get_sock_fd() { return this->sock.fd; }

int msrv::Server::get_binding_status() { return this->binding_status; }

int msrv::Server::get_listener_status() { return this->listener_status; }

struct sockaddr_in *msrv::Server::get_sock_addr() {
  return &this->sock_addr;
}

void msrv::Server::set_sock(m_socket sock) { this->sock = sock; }

void msrv::Server::set_sock_addr(struct sockaddr_in sock_addr) {
  this->sock_addr = sock_addr;
}

void msrv::Server::set_binding_status(int binding_status) {
  this->binding_status = binding_status;
}

void msrv::Server::set_listener_status(int listener_status) {
  this->listener_status = listener_status;
}

void msrv::Server::close_sock() {
  close(this->sock.fd);
  this->binding_status = -1;
  this->listener_status = -1;
  this->sock.fd = -1;
}

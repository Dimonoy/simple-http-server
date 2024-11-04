#ifndef NETWORK_SERVER_BUILDER_HPP
#define NETWORK_SERVER_BUILDER_HPP

#include "server.hpp"

namespace msrv {

class ServerBuilder {
private:
  Server *server;

public:
  ServerBuilder();
  ~ServerBuilder();
  void reset_server();

  void build_sock(uint8_t domain, uint8_t type);
  void build_binding(sa_family_t sin_family, in_port_t port, in_addr_t addr);
  void build_listener(uint8_t n_to_listen);

  Server *get_server();
};

} // namespace msrv

#endif // NETWORK_SERVER_BUILDER_HPP

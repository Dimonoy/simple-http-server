#include "network/server_director.hpp"

void msrv::ServerDirector::setup_server(msrv::ServerBuilder *server_builder) {
  server_builder->build_sock(AF_INET, SOCK_STREAM);
  server_builder->build_binding(AF_INET, 8080, INADDR_ANY);
  server_builder->build_listener(5);
}

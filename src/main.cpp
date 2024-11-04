#include "network/server.hpp"
#include "network/server_builder.hpp"
#include "network/server_director.hpp"
#include <iostream>

#include "main.hpp"

const uint16_t BUFFER_SIZE = 256;

int main() {
  using namespace msrv;

  char buffer[BUFFER_SIZE];

  ServerBuilder *server_builder = new ServerBuilder();
  ServerDirector *server_director = new ServerDirector();
  server_director->setup_server(server_builder);

  Server *server = server_builder->get_server();

  std::cout << "--- Running Server ---" << std::endl;
  std::cout << "Socket file decriptor: " << server->get_sock_fd() << std::endl;
  std::cout << "Socket binding status: " << server->get_binding_status()
            << std::endl;
  std::cout << "Socket listener status: " << server->get_listener_status()
            << std::endl;

  server->close_sock();

  std::cout << "--- Closed Server ---" << std::endl;
  std::cout << "Socket file decriptor: " << server->get_sock_fd() << std::endl;
  std::cout << "Socket binding status: " << server->get_binding_status()
            << std::endl;
  std::cout << "Socket listener status: " << server->get_listener_status()
            << std::endl;

  delete server;
  delete server_builder;
  delete server_director;

  return 0;
}

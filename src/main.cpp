#include "main.hpp"

const uint16_t BUFFER_SIZE = 256;

void msrv::call_error(const std::string& msg) {
  std::cerr << "[ERROR] " << msg << std::endl;
  exit(EXIT_FAILURE);
}

int msrv::Server::get_sock_fd() {
  return this->sock.fd;
}

int msrv::Server::get_binding_status() {
  return this->binding_status;
}

int msrv::Server::get_listener_status() {
  return this->listener_status;
}

struct sockaddr_in* msrv::Server::get_sock_addr() {
  return &this->sock_addr;
}

void msrv::Server::set_sock(m_socket sock) {
  this->sock = sock;
}

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

msrv::ServerBuilder::ServerBuilder() {
  this->reset_server();
}

msrv::ServerBuilder::~ServerBuilder() {
  delete server;
}

void msrv::ServerBuilder::reset_server() {
  this->server = new Server();
}

void msrv::ServerBuilder::build_sock(uint8_t domain, uint8_t type) {
  m_socket sock;
  sock.domain = domain;
  sock.type = type;
  sock.fd = socket(sock.domain, sock.type, sock.protocol);

  if (sock.fd < 0)
    msrv::call_error("Socket connection failed");

  this->server->set_sock(sock);
}

void msrv::ServerBuilder::build_binding(sa_family_t sin_family, in_port_t port, in_addr_t addr) {
  struct sockaddr_in sock_addr;
  sock_addr.sin_family = sin_family;
  sock_addr.sin_port = port;
  sock_addr.sin_addr.s_addr = addr;
  server->set_sock_addr(sock_addr);

  int binding_status = bind(this->server->get_sock_fd(), (struct sockaddr*)&sock_addr, sizeof(sock_addr));
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

msrv::Server* msrv::ServerBuilder::get_server() {
  Server* server = this->server;
  this->reset_server();

  return server;
}

void msrv::ServerDirector::setup_server(msrv::ServerBuilder* server_builder) {
  server_builder->build_sock(AF_INET, SOCK_STREAM);  
  server_builder->build_binding(AF_INET, 8080, INADDR_ANY);
  server_builder->build_listener(5);
}

int main() {
  using namespace msrv;

  char buffer[BUFFER_SIZE];

  ServerBuilder* server_builder = new ServerBuilder();
  ServerDirector* server_director = new ServerDirector();
  server_director->setup_server(server_builder);

  Server* server = server_builder->get_server();

  std::cout << "--- Running Server ---" << std::endl;
  std::cout << "Socket file decriptor: " << server->get_sock_fd() << std::endl;
  std::cout << "Socket binding status: " << server->get_binding_status() << std::endl;
  std::cout << "Socket listener status: " << server->get_listener_status() << std::endl;

  server->close_sock();

  std::cout << "--- Closed Server ---" << std::endl;
  std::cout << "Socket file decriptor: " << server->get_sock_fd() << std::endl;
  std::cout << "Socket binding status: " << server->get_binding_status() << std::endl;
  std::cout << "Socket listener status: " << server->get_listener_status() << std::endl;

  delete server;
  delete server_builder;
  delete server_director;

  return 0;
}

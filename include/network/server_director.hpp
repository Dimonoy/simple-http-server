#ifndef NETWORK_SERVER_DIRECTOR_HPP
#define NETWORK_SERVER_DIRECTOR_HPP

#include "server_builder.hpp"

namespace msrv {

class ServerDirector {
public:
  void setup_server(ServerBuilder *server_builder);
};

} // namespace msrv

#endif // NETWORK_SERVER_DIRECTOR_HPP

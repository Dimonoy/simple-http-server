#include <iostream>

#include "utils/error.hpp"

void msrv::call_error(const std::string &msg) {
  std::cerr << "[ERROR] " << msg << std::endl;
  exit(EXIT_FAILURE);
}


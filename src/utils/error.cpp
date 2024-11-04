#include "error.hpp"
#include <stdlib.h>
#include <iostream>

void msrv::call_error(const std::string& msg) {
  std::cerr << "[ERROR] " << msg << std::endl;
  exit(EXIT_FAILURE);
}

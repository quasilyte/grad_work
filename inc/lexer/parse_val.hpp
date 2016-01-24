#pragma once

#include <cstdlib>

#include "runtime/core/types.hpp"

inline real parse_real(const char *val) {
  return atof(val);
}

inline decimal parse_decimal(const char *val) {
  return atol(val);
}

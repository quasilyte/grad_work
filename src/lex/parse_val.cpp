#include "lex/parse_val.hpp"

#include <cstdlib>

real lex::parse_real(const char *val) {
  return atof(val);
}

integer lex::parse_integer(const char *val) {
  return atol(val);
}

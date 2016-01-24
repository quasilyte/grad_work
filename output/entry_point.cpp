// Those should be set via command line...
#define LUA
#define ARITH

#ifdef LUA
# ifdef ARITH
#  include "lua/arith.hpp"
# endif
#endif

int main(void) {
  program();
  return 0;
}

#include "../../inc/runtime/core/types.hpp"
#include "../../inc/runtime/opt/io.hpp"

decimal sum(decimal x, decimal y) {
  return x + y;
}

void program() {
  print(sum(2, 4));
}

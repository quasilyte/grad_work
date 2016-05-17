#include "backend/cpp/rt/any.hpp"
#include <cstdio>

// (range 10)
// (range 0 10)
// (range 0 10 1)

// if range is used:
// 1) generate struct
// 2) generate only used functions
// (#struct range (int low high step))

int main() {
  {
    Any_ arr{Arrays_::New(4)};
  }
  // Array_ arr = Arrays_::New(4);
  /*
  {
    ArrayHandle_ x = Arrays_::New(4);
    set_(x, 0, 43);
    printf("%ld\n", nth_(x, 0));
    puts("--");
  }
  {
    ArrayHandle_ x = Arrays_::New(4);
    set_(x, 0, 43);
    printf("%ld\n", nth_(x, 0));
    puts("--");
  }*/

  return 0;
}

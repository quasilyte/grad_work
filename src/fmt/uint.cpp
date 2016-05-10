#include "fmt/uint.hpp"

#include <cmath>

namespace fmt {
  constexpr u64 operator "" _zeros(unsigned long long n) {
    return std::pow<u64>(static_cast<u64>(10), n);
  }
}

u32 fmt::width(u32 x) {
  if (x < 6_zeros) {
    if (x < 2_zeros) {
      return x < 1_zeros ? 1 : 2;
    } else {
      if (x < 3_zeros) {
        return 3;
      } else if (x < 4_zeros) {
        return 4;
      } else {
        return 5;
      }
    }
  } else {
    if (x < 7_zeros) {
      return x < 6_zeros ? 6 : 7;
    } else {
      if (x < 8_zeros) {
        return 8;
      } else if (x < 9_zeros) {
        return 9;
      } else {
        return 10;
      }
    }
  }
}

u32 fmt::width(u64 x) {
  if (x < 11_zeros) {
    if (x < 5_zeros) {
      if (x < 1_zeros) {
        return 1;
      } else if (x < 2_zeros) {
        return 2;
      } else if (x < 3_zeros) {
        return 3;
      } else if (x < 4_zeros) {
        return 4;
      } else {
        return 5;
      }
    } else {
      if (x < 6_zeros) {
        return 6;
      } else if (x < 7_zeros) {
        return 7;
      } else if (x < 8_zeros) {
        return 8;
      } else if (x < 9_zeros) {
        return 9;
      } else {
        return 10;
      }
    }
  } else {
    if (x < 15_zeros) {
      if (x < 11_zeros) {
        return 11;
      } else if (x < 12_zeros) {
        return 12;
      } else if (x < 13_zeros) {
        return 13;
      } else if (x < 14_zeros) {
        return 14;
      } else {
        return 15;
      }
    } else {
      if (x < 16_zeros) {
        return 16;
      } else if (x < 17_zeros) {
        return 17;
      } else if (x < 18_zeros) {
        return 18;
      } else if (x < 19_zeros) {
        return 19;
      } else {
        return 20;
      }
    }
  }
}

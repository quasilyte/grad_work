#include <cstdio>
#include <utility>

#include "core.hpp"

namespace cpp_rt {
  class Range;
}

struct FpRange {
  Int_ low;
  Int_ high;
  Int_ step;
};

FpRange range(Int_ high) {
  return FpRange{0_i, high, 1_i};
}

FpRange next(const FpRange& r) {
  return FpRange{r.low + r.step, r.high, r.step};
  // r.low += r.step;
  // return r;
}

bool has_next(FpRange r) {
  return r.low < r.high;
}

int current(FpRange r) {
  return r.low;
}

class cpp_rt::Range {
public:
  Range(Int_ high): high{high} {}
  Range(Int_ low, Int_ high): low{low}, high{high} {}
  Range(Int_ low, Int_ high, Int_ step): low{low}, high{high}, step{step} {}

  void Next() {
    low += step;
  }

  int Current() {
    return low;
  }

  bool HasNext() const noexcept {
    return low < high;
  }
  
  Int_ low = 0_i;
  Int_ high;
  Int_ step = 1_i;
};

using namespace cpp_rt;

const Int_ N = 3999;

Int_ test_oop(Int_ m) {
  Int_ score = 0_i;
  for (Int_ i = 0_i; i < N; ++i) {
    for (Range r{m + i}; r.HasNext(); r.Next()) {
      score += r.Current() % 2;
    }
  }
  return score;
}

Int_ test_fp(Int_ m) {
  Int_ score = 0_i;
  for (Int_ i = 0_i; i < N; ++i) {
    for (FpRange r = range(m + i); has_next(r); r = next(r)) {
      score += current(r) % 2;
    }
  }
  return score;
}

int main(int argc, char* argv[]) {
  printf("%ld\n", test_oop(argc * 29999));
  // printf("%ld\n", test_fp(argc * 29999));
  
  return 0;
}

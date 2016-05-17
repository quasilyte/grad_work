#include <stdio.h>

#include "core.h"

typedef struct Range Range;
struct Range {
  Int_ low;
  Int_ high;
  Int_ step;
};

Range range(Int_ high) {
  return (Range){0, high, 1};
}

Range fp_next(Range r) {
  return (Range){r.low + r.step, r.high, r.step};
}

void next(Range* r) {
  r->low += r->step;
}

Bool_ has_next(Range r) {
  return r.low < r.high;
}

int current(Range r) {
  return r.low;
}

const Int_ N = 3999;

Int_ test_oop(Int_ m) {
  Int_ score = 0;
  for (Int_ i = 0; i < N; ++i) {
    for (Range r = range(m + i); has_next(r); next(&r)) {
      score += current(r) % 2;
    }
  }
  return score;
}

Int_ test_fp(Int_ m) {
  Int_ score = 0;
  for (Int_ i = 0; i < N; ++i) {
    for (Range r = range(m + i); has_next(r); r = fp_next(r)) {
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

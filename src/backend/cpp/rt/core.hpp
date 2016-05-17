#pragma once

#include <cstdint>
#include <stdint.h>

typedef int64_t Int_;
typedef double Real_;
typedef bool Bool_;

inline Real_ operator "" _r(long double val) {
  return static_cast<Real_>(val);
}

inline Int_ operator "" _i(unsigned long long val) {
  return static_cast<Int_>(val);
}

static inline Int_ int_(Int_ x) { return x; }
static inline Int_ int_(Real_ x) { return static_cast<Int_>(x); }

static inline Real_ real_(Real_ x) { return x; }
static inline Real_ real_(Int_ x) { return static_cast<Real_>(x); }

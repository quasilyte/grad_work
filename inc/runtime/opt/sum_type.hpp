#pragma once

#include "runtime/core/types.hpp"

class Any {
  enum { D, R } tag;
  union {
    decimal d;
    real r;
  } value;

public:
  Any(decimal d): tag{D} {
    value.d = d;
  }

  Any(real r): tag{R} {
    value.r = r;
  }

  friend Any add(const Any lhs, const Any rhs);

  decimal to_decimal() const {
    switch (tag) {
    case D: return value.d;
    case R: return static_cast<decimal>(value.r);
    default: throw "unknown type tag";
    }
  }

  real to_real() const {
    switch (tag) {
    case D: return static_cast<real>(value.d);
    case R: return value.r;
    default: throw "unknown type tag";
    }
  }
};

Any add(const Any lhs, const Any rhs) {
  switch (lhs.tag) {
  case lhs.D:
    return Any(lhs.value.d + rhs.to_decimal());
  case lhs.R:
    return Any(lhs.value.r + rhs.to_real());
  default: throw "unknown type tag";
  }
}

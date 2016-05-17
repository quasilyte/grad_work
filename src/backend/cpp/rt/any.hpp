#include "core.hpp"
#include "array.hpp"
#include <vector>

// bool
// int
// real
// str
// symbol
// list[T]
// vector

struct Any_ {
  Any_(Int_ x): tag{INT}, int_datum{x} {}
  Any_(Real_ x): tag{REAL}, real_datum{x} {}
  Any_(const ArrayHandle_&& x): tag{ARRAY}, array_datum{x.id} {}

  enum {
    INT,
    REAL,
    ARRAY,
  } tag;

  ~Any_() {}
  
  union {
    Int_ int_datum;
    Real_ real_datum;
    ArrayHandle_ array_datum;

    // Datum(Int_ i): i{i} {}
    // Datum(Real_ r): r{r} {}
  };
};

Any_ any_(Int_ x) {
  return Any_{x};
}

Any_ any_(Real_ x) {
  return Any_{x};
}

Int_ int_(Any_ x) {
  switch (x.tag) {
  case Any_::INT: return x.int_datum;
  case Any_::REAL: return static_cast<Int_>(x.real_datum);
  default: throw "invalid int()";
  }
}

Real_ real_(Any_ x) {
  switch (x.tag) {
  case Any_::INT: return static_cast<Real_>(x.int_datum);
  case Any_::REAL: return x.real_datum;
  default: throw "invalid real()";
  }
}

#include "core.h"

typedef struct Any_ Any_;
struct Any_ {
  enum {
    INT_,
    REAL_
  } tag;
  
  union {
    Int_ int_datum;
    Real_ real_datum;
  };
};

static inline Any_ any_Int_(Int_ x) {
  return (Any_){INT_, {.int_datum = x}};
}

static inline Any_ any_Real_(Real_ x) {
  return (Any_){REAL_, {.real_datum = x}};
}

static inline Int_ int_Any_(Any_ x) {
  switch (x.tag) {
  case INT_: return x.int_datum;
  case REAL_: return (Int_)x.real_datum;
  default: error("int_Any_: unkown tag");
  }
}

static inline Real_ real_Any_(Any_ x) {
  switch (x.tag) {
  case INT_: return (Real_)x.int_datum;
  case REAL_: return x.real_datum;
  default: error("real_Any_: unkown tag");
  }
}

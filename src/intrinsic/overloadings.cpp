#include "intrinsic/overloadings.hpp"

using namespace sym;

Type intrinsic::num_overloading(Type x) {
  switch (x.Tag()) {
  case Type::ANY: return Type::ANY_TO_NUM;
  case Type::INT: return Type::INT_TO_NUM;
  case Type::REAL: return Type::REAL_TO_NUM;

  default:
    throw "num_overloading: arg type not match";
  }
}

Type intrinsic::real_overloading(Type x) {
  switch (x.Tag()) {
  case Type::ANY: return Type::ANY_TO_REAL;
  case Type::NUM: return Type::NUM_TO_REAL;
  case Type::INT: return Type::INT_TO_REAL;

  default:
    throw "num_overloading: arg type not match";
  }
}

Type intrinsic::int_overloading(Type x) {
  switch (x.Tag()) {
  case Type::ANY: return Type::ANY_TO_INT;
  case Type::NUM: return Type::NUM_TO_INT;
  case Type::REAL: return Type::REAL_TO_INT;

  default:
    throw "num_overloading: arg type not match";
  }
}
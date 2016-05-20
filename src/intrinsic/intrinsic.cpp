#include "intrinsic/intrinsic.hpp"

using namespace sym;

Type one_arg(uint idx, Type ty) {
  if (idx == 0) {
    return ty;
  } else {
    throw "param_of: arity error";
  }
}

Type intrinsic::ret_type_of(Type f) {
  switch (f.Tag()) {
  case Type::ANY_TO_INT:
  case Type::REAL_TO_INT:
    return Type::Int();

  case Type::ANY_TO_REAL:
  case Type::INT_TO_REAL:
    return Type::Real();

  default:
    throw "ret_type_of: unknown intrinsic";
  }
}

uint intrinsic::arity_of(Type f) {
  switch (f.Tag()) {
  case Type::ANY_TO_INT:
  case Type::ANY_TO_REAL:
  case Type::REAL_TO_INT:
  case Type::INT_TO_REAL:
   return 1;

  default:
    throw "ret_type_of: unknown intrinsic";
  }
}

Type intrinsic::param_of(Type f, uint idx) {
  switch (f.Tag()) {
  case Type::ANY_TO_INT: return one_arg(idx, Type::Any());
  case Type::ANY_TO_REAL: return one_arg(idx, Type::Any());
  case Type::INT_TO_REAL: return one_arg(idx, Type::Int());
  case Type::REAL_TO_INT: return one_arg(idx, Type::Real());

  default:
    throw "param_of: unknown intrinsic";
  }
}
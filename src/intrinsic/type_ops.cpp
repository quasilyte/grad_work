#include "intrinsic/type_ops.hpp"

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

  case Type::INT_TO_ANY:
  case Type::REAL_TO_ANY:
    return Type::Any();

  default:
    throw "ret_type_of: unknown intrinsic";
  }
}

uint intrinsic::arity_of(Type f) {
  switch (f.Tag()) {
  case Type::ANY_TO_INT: // (int x)
  case Type::REAL_TO_INT:
  case Type::ANY_TO_REAL: // (real x)
  case Type::INT_TO_REAL:
  case Type::INT_TO_ANY: // (any x)
  case Type::REAL_TO_ANY:
   return 1;

  default:
    throw "ret_type_of: unknown intrinsic";
  }
}

Type intrinsic::param_of(Type f, uint idx) {
  switch (f.Tag()) {
  case Type::ANY_TO_REAL:
  case Type::ANY_TO_INT:
    return one_arg(idx, Type::Any());

  case Type::REAL_TO_INT:
  case Type::REAL_TO_ANY:
    return one_arg(idx, Type::Real());

  case Type::INT_TO_REAL:
  case Type::INT_TO_ANY:
    return one_arg(idx, Type::Int());

  default:
    throw "param_of: unknown intrinsic";
  }
}

Type intrinsic::cast(Type from, Type to) {
  switch (from.Tag()) {
  case Type::INT:
    switch (to.Tag()) {
    case Type::REAL: return Type::INT_TO_REAL;
    case Type::ANY: return Type::INT_TO_ANY;

    default:
      throw "unsupported typecast";
    }

  case Type::REAL:
    switch (to.Tag()) {
    case Type::INT: return Type::REAL_TO_INT;
    case Type::ANY: return Type::REAL_TO_ANY;

    default:
      throw "unsupported typecast";
    }

  case Type::ANY:
    switch (to.Tag()) {
    case Type::INT: return Type::ANY_TO_INT;
    case Type::REAL: return Type::ANY_TO_REAL;

    default:
      throw "unsupported typecast";
    }

  default:
    throw "unsupported typecast";
  }
}



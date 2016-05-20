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
  case Type::NUM_TO_INT:
  case Type::REAL_TO_INT:
    return Type::Int();

  case Type::ANY_TO_REAL:
  case Type::NUM_TO_REAL:
  case Type::INT_TO_REAL:
    return Type::Real();

  case Type::ANY_TO_NUM:
  case Type::REAL_TO_NUM:
  case Type::INT_TO_NUM:
    return Type::Num();

  default:
    throw "ret_type_of: unknown intrinsic";
  }
}

uint intrinsic::arity_of(Type f) {
  switch (f.Tag()) {
  case Type::ANY_TO_INT: // (int x)
  case Type::NUM_TO_INT:
  case Type::REAL_TO_INT:
  case Type::ANY_TO_REAL: // (real x)
  case Type::NUM_TO_REAL:
  case Type::INT_TO_REAL:
  case Type::ANY_TO_NUM: // (num x)
  case Type::REAL_TO_NUM:
  case Type::INT_TO_NUM:
   return 1;

  default:
    throw "ret_type_of: unknown intrinsic";
  }
}

Type intrinsic::param_of(Type f, uint idx) {
  switch (f.Tag()) {
  case Type::ANY_TO_NUM:
  case Type::ANY_TO_REAL:
  case Type::ANY_TO_INT:
    return one_arg(idx, Type::Any());

  case Type::NUM_TO_REAL:
  case Type::NUM_TO_INT:
    return one_arg(idx, Type::Num());

  case Type::REAL_TO_NUM:
  case Type::REAL_TO_INT:
    return one_arg(idx, Type::Real());

  case Type::INT_TO_NUM:
  case Type::INT_TO_REAL:
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
      case Type::NUM: return Type::INT_TO_NUM;

      default:
        throw "unsupported typecast";
      }

    case Type::REAL:
      switch (to.Tag()) {
      case Type::INT: return Type::REAL_TO_INT;
      case Type::NUM: return Type::REAL_TO_NUM;

      default:
        throw "unsupported typecast";
      }

    case Type::NUM:
      switch (to.Tag()) {
      case Type::INT: return Type::NUM_TO_INT;
      case Type::REAL: return Type::NUM_TO_REAL;

      default:
        throw "unsupported typecast";
      }

    default:
      throw "unsupported typecast";
    }
}

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

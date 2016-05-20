#include "backend/cpp/cg/type_map.hpp"

#include "dt/str_view.hpp"
#include "sym/type.hpp"

using namespace sym;
using namespace dt;

StrView& cpp_cg::type_name(Type ty) {
  static StrView int_name{"Int_", 4};
  static StrView real_name{"Real_", 5};
  static StrView num_name{"Num_", 4};
  static StrView str_name{"Str_", 4};
  static StrView sym_name{"Sym_", 4};
  static StrView any_name{"Any_", 4};
  static StrView void_name{"void", 4};

  switch (ty.Tag()) {
  case Type::INT: return int_name;
  case Type::REAL: return real_name;
  case Type::NUM: return num_name;
  case Type::STR: return str_name;
  case Type::SYM: return sym_name;
  case Type::ANY: return any_name;
  case Type::VOID: return void_name;

  default:
    throw "type_name: unknown type";
  }
}

StrView& cpp_cg::intrinsic_name(Type ty) {
  static StrView any_to_int{"any_to_int_"};
  static StrView num_to_int{"num_to_int_"};
  static StrView real_to_int{"real_to_int_"};
  static StrView any_to_real{"any_to_real_"};
  static StrView num_to_real{"num_to_real_"};
  static StrView int_to_real{"int_to_real_"};
  static StrView any_to_num{"any_to_num_"};
  static StrView real_to_num{"real_to_num_"};
  static StrView int_to_num{"int_to_num_"};


  switch (ty.Tag()) {
  case Type::ANY_TO_INT: return any_to_int;
  case Type::NUM_TO_INT: return num_to_int;
  case Type::REAL_TO_INT: return real_to_int;
  case Type::ANY_TO_REAL: return any_to_real;
  case Type::NUM_TO_REAL: return num_to_real;
  case Type::INT_TO_REAL: return int_to_real;
  case Type::ANY_TO_NUM: return any_to_num;
  case Type::REAL_TO_NUM: return real_to_num;
  case Type::INT_TO_NUM: return int_to_num;

  default:
    throw "intrinsic_name: unknown type";
  }
}

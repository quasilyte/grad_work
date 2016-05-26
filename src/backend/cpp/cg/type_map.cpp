#include "backend/cpp/cg/type_map.hpp"

#include "dt/str_view.hpp"
#include "sym/type.hpp"

using namespace sym;
using namespace dt;

StrView& cpp_cg::type_name(Type ty) {
  static StrView int_name{"Int"};
  static StrView real_name{"Real"};
  static StrView str_name{"Str"};
  static StrView sym_name{"Sym"};
  static StrView any_name{"Any"};
  static StrView void_name{"void"};

  switch (ty.Tag()) {
  case Type::INT: return int_name;
  case Type::REAL: return real_name;
  case Type::STR: return str_name;
  case Type::SYM: return sym_name;
  case Type::ANY: return any_name;
  case Type::VOID: return void_name;

  default:
    throw "type_name: unknown type";
  }
}

StrView& cpp_cg::intrinsic_name(Type ty) {
  static StrView any_to_int{"any_to_int"};
  static StrView real_to_int{"real_to_int"};
  static StrView any_to_real{"any_to_real"};
  static StrView int_to_real{"int_to_real"};
  static StrView int_to_any{"int_to_any"};
  static StrView real_to_any{"real_to_any"};

  switch (ty.Id()) {
  case Type::ANY_TO_INT: return any_to_int;
  case Type::REAL_TO_INT: return real_to_int;
  case Type::ANY_TO_REAL: return any_to_real;
  case Type::INT_TO_REAL: return int_to_real;
  case Type::INT_TO_ANY: return int_to_any;
  case Type::REAL_TO_ANY: return real_to_any;

  default:
    throw "intrinsic_name: unknown type";
  }
}

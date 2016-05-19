#include "backend/cpp/cg/type_map.hpp"

#include "dt/str_view.hpp"
#include "sym/type.hpp"

using namespace sym;

dt::StrView int_name{"Int_", 4};
dt::StrView real_name{"Real_", 5};
dt::StrView num_name{"Num_", 4};
dt::StrView str_name{"Str_", 4};
dt::StrView sym_name{"Sym_", 4};
dt::StrView any_name{"Any_", 4};
dt::StrView void_name{"void", 4};

dt::StrView& cpp_cg::type_name(sym::Type ty) {
  switch (ty.Tag()) {
  case Type::INT_ID: return int_name;
  case Type::REAL_ID: return real_name;
  case Type::NUM_ID: return num_name;
  case Type::STR_ID: return str_name;
  case Type::SYM_ID: return sym_name;
  case Type::ANY_ID: return any_name;
  case Type::VOID_ID: return void_name;
  case Type::UNKNOWN_ID: throw "type_name: unknown type";

  default:
    throw "type_name: undefined type";
  }
}

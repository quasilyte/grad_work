#include "backend/cpp/cg/type_map.hpp"

#include "dt/str_view.hpp"

using namespace sym;

dt::StrView int_name{"int_", 4};
dt::StrView real_name{"real_", 5};
dt::StrView num_name{"num_", 4};
dt::StrView str_name{"str_", 4};

dt::StrView& cpp_cg::type_name(sym::Type ty) {
  switch (ty.Tag()) {
  case Type::INT: return int_name;
  case Type::REAL: return real_name;
  case Type::NUM: return num_name;
  case Type::STR: return str_name;

  default:
    throw "cant map type to name";
  }
}

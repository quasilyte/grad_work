#include "frontend/go_cc/types.hpp"

#include "mn_hash.hpp"
#include "dt/str_view.hpp"

using namespace go_cc;
using sym::Type;

sym::Type go_cc::type_by_name(const dt::StrView& name) {
  using namespace mn_hash;

  switch (encode9(name.Data(), name.Len())) {
  case encode9("int"): return Type::Int();
  case encode9("int64"): return Type::Int();
  case encode9("float64"): return Type::Real();
  case encode9("string"): return Type::Str();

  default:
    throw "type_by_name: unknown type";
  }
}

const char* go_cc::name_by_type(sym::Type type) {
  switch (type.Tag()) {
  case Type::INT: return "int";
  case Type::REAL: return "real";
  case Type::BOOL: return "bool";
  case Type::VOID: return "void";

  default: return "???";
  }
}

#include <frontend/go_cc/common/types.hpp>

#include <mn_hash.hpp>
#include <dt/str_view.hpp>
#include <err/type_errors.hpp>
#include <unit/structs.hpp>

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
    auto st = unit::get_struct(name);

    if (st) {
      return st->type;
    } else {
      throw err::UndefinedType{name};
    }
  }
}

const char* go_cc::name_by_type(sym::Type type) {
  switch (type.Tag()) {
  case Type::INT: return "int";
  case Type::REAL: return "real";
  case Type::BOOL: return "bool";
  case Type::VOID: return "void";
  case Type::STR: return "string";

  default: return "???";
  }
}

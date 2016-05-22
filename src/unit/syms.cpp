#include "unit/syms.hpp"

#include "dt/dict.hpp"

using namespace sym;

dt::Dict<sym::Type> globals;

void unit::def_global(dt::StrView name, Type type) {
  if (globals.Find(name).IsVoid()) {
    globals.Put(name, type);
  } else {
    throw "def_global: redefinition is not allowed";
  }
}

Type unit::get_global(dt::StrView name) {
  return globals.Find(name);
}

#include "unit/globals.hpp"

#include "dt/dict.hpp"
#include <deps/cxx/vector.hpp>

using namespace sym;

dt::Dict<sym::Global*> globals_name_map;
std::vector<sym::Global*> globals_id_map;

void unit::def_global(dt::StrView name, ast::Node* val, Type type) {
  if (globals_name_map.Find(name)) {
    throw "def_global: redefinition is not allowed";
  } else {
    auto global = new Global{name, val, type};

    globals_name_map.Put(name, global);
    globals_id_map.push_back(global);
  }
}

Global* unit::get_global(dt::StrView name) {
  return globals_name_map.Find(name);
}

Global* unit::get_global(uint idx) {
  return globals_id_map[idx];
}

uint unit::global_count() {
  return globals_name_map.Size();
}

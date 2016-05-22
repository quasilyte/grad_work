#include "unit/structs.hpp"

#include "dt/dict.hpp"

using namespace sym;
using namespace dt;

std::vector<sym::Struct*> type_id_map;
Dict<sym::Struct*> type_name_map;

void unit::def_struct(dt::StrView name, Struct::AttrList&& attrs) {
  if (type_name_map.Find(name)) {
    throw "def_struct: redefinition of struct";
  } else {
    auto st_id = Type::StructTag(type_name_map.Size());
    auto st = new sym::Struct{name, std::move(attrs), sym::Type{st_id}};

    type_name_map.Put(name, st);
    type_id_map.push_back(st);
  }
}

sym::Struct* unit::get_struct(dt::StrView name) {
  return type_name_map.Find(name);
}

sym::Struct* unit::get_struct(Type type) {
  return type_id_map[Type::StructKey(type.Tag())];
}

sym::Struct* unit::get_struct(uint idx) {
  return type_id_map[idx];
}

uint unit::struct_count() {
  return type_id_map.size();
}

#include <unit/structs.hpp>

#include <dt/dict.hpp>
#include <sym/rules.hpp>
#include <dev_assert.hpp>

using namespace sym;
using namespace dt;

std::vector<sym::Struct*> type_id_map;
Dict<sym::Struct*> type_name_map;

void unit::declare_struct(dt::StrView name) {
  if (type_name_map.Find(name)) {
    // throw err::Redefinition{name, "struct"};
    throw "redefenition";
  } else {
    auto st = new sym::Struct{name, sym::Type::Struct(type_name_map.Size())};

    type_name_map.Put(name, st);
    type_id_map.push_back(st);
  }
}

void unit::def_struct(dt::StrView name, Struct::AttrList&& attrs) {
  if (!is_type_name(name)) {
    throw "def_struct: struct name must start with capital letter";
  }

  if (type_name_map.Find(name)) {
    throw "def_struct: redefinition of struct";
  } else {
    auto st = new sym::Struct{
      name,
      std::move(attrs),
      sym::Type::Struct(type_name_map.Size())
    };

    type_name_map.Put(name, st);
    type_id_map.push_back(st);
  }
}

sym::Struct* unit::get_struct(dt::StrView name) {
  return type_name_map.Find(name);
}

sym::Struct* unit::get_struct(Type type) {
  dev_assert(type.IsStruct());
  return type_id_map[type.Id()];
}

sym::Struct* unit::get_struct(uint idx) {
  return type_id_map[idx];
}

uint unit::struct_count() {
  return type_id_map.size();
}

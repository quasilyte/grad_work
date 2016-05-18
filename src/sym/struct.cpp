#include "sym/struct.hpp"

using namespace sym;

Struct::Struct(dt::StrView name, std::vector<Param>&& attrs, Type ty):
name{name}, attrs{attrs}, type{ty} {}

sym::Param* Struct::Attr(dt::StrView name) {
  for (uint i = 0; i < attrs.size(); ++i) {
    if (attrs[i].name == name) {
      return &attrs[i];
    }
  }

  return nullptr;
}

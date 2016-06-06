#include <sym/struct.hpp>

using namespace sym;

Struct::Struct(dt::StrView name, AttrList&& attrs, Type ty):
name{name}, attrs{attrs}, type{ty} {}

Struct::Struct(dt::StrView name, Type ty):
name{name}, type{ty} {}

sym::Param* Struct::Attr(dt::StrView name) {
  for (uint i = 0; i < attrs.size(); ++i) {
    if (attrs[i].name == name) {
      return &attrs[i];
    }
  }

  return nullptr;
}

void Struct::Define(AttrList&& attrs) {
  this->attrs = attrs;
}

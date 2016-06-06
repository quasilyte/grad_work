#pragma once

#include <deps/cxx/vector.hpp>
#include "dt/str_view.hpp"
#include "sym/param.hpp"
#include "sym/type.hpp"

namespace sym {
  struct Struct;
}

struct sym::Struct {
  typedef std::vector<sym::Param> AttrList;

  dt::StrView name;
  AttrList attrs;
  sym::Type type;

  Struct(dt::StrView, AttrList&&, sym::Type);
  Struct(dt::StrView, sym::Type);

  sym::Param* Attr(dt::StrView name);

  void Define(AttrList&&);
};

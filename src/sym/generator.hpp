#pragma once

#include "typedefs.hpp"
#include "dt/str_view.hpp"

namespace sym {
  class Generator;
}

class sym::Generator {
public:
  typedef u32 Id;

  Generator();
  ~Generator();

  Id NextId();
  const dt::StrView* Next();
  const dt::StrView* Get(Id id);

private:
  dt::StrView* pool;
  Id current_id;
  Id count;
};

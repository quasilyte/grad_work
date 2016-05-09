#pragma once

#include "typedefs.hpp"
#include "dt/str_view.hpp"

namespace sym {
  class Generator;
}

class sym::Generator {
public:
  Generator();
  ~Generator();

  u64 NextId();
  const dt::StrView* Next();
  const dt::StrView* Get(u64 id);

private:
  dt::StrView* pool;
  u64 current_id;
  u64 count;
};

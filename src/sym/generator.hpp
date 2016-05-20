#pragma once

#include "typedefs.hpp"
#include "dt/str_view.hpp"

namespace sym {
  class Generator;
}

class sym::Generator {
public:
  typedef u32 Id;

  Generator(char prefix);
  ~Generator();

  Id NextId();
  const dt::StrView* Next();
  const dt::StrView* Get(Id id);

  void Drop(int n);

private:
  char prefix;
  dt::StrView* pool;
  Id current_id;
  Id count;
};

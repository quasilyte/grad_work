#pragma once

#include "typedefs.hpp"
#include "dt/str_view.hpp"
#include <deps/cxx/vector.hpp>

namespace sym {
  class Generator;
}

class sym::Generator {
public:
  typedef u32 Id;

  Generator(char prefix, int cap = 32);
  ~Generator();

  Id NextId();
  Id CurrentId() const noexcept;

  const dt::StrView& GetNext();
  const dt::StrView& Get(Id id);

  void GenerateAll();

private:
  char prefix;
  std::vector<dt::StrView> pool;
  Id current_id = 0;

  void Generate(Id id);
};

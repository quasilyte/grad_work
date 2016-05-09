#pragma once

#include "sym/type.hpp"
#include <vector>

namespace sym {
  class Func;
}

class sym::Func {
public:
  Func() = default; // #FIXME: should not exist
  Func(int arity);
  Func(sym::Type* ret_type, std::vector<sym::Type*>&& params);

  // int MinArity() const noexcept;
  // int MaxArity() const noexcept;
  int Arity() const noexcept;

private:
  Type* ret_type;
  std::vector<Type*> params;
};

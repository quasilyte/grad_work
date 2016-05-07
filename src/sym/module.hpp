#pragma once

#include "dt/str_view.hpp"
#include "dt/dict.hpp"
#include "sym/type.hpp"

namespace sym {
  class Module;
}

class sym::Module {
public:
  Module(const char* name);

  const dt::StrView& Name() const noexcept;

  void DefineSymbol(dt::StrView name, Type);

  const sym::Type& Symbol(dt::StrView name) const;

private:
  dt::StrView name;
  mutable dt::Dict<Type> symbols;
  // + signatures for functions
};

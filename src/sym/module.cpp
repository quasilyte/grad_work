#include "sym/module.hpp"

#include "dbg/dt.hpp"

using namespace sym;

Module::Module(const char *name): name{dt::StrView{name}} {}

void Module::DefineSymbol(dt::StrView name, Type type) {
  if (symbols.Get(name).Defined()) {
    throw "already defined";
  } else {
    type.MarkDefined();
    symbols.Put(name, type);
  }
}

const sym::Type& Module::Symbol(dt::StrView name) const {
  return symbols.Get(name);
}

sym::Type& Module::SymbolMut(dt::StrView name) {
  return symbols.GetMut(name);
}

const dt::StrView& Module::Name() const noexcept {
  return name;
}

#include "sym/module.hpp"

#include "dbg/dt.hpp"

using namespace sym;

Module::Module(const char *name): name{dt::StrView{name}} {}

void Module::DefineSymbol(dt::StrView name, Type type) {
  sym::Type symbol = symbols.Get(name);

  if (symbol.IsVoid()) {
    symbols.Put(name, type);
  } else {
    throw "already defined";
  }
}

void Module::SetSymbolType(dt::StrView name, Type type) {
  symbols.Put(name, type);
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

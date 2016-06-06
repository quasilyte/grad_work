#include "sym/module.hpp"

/*
#include <deps/c/math.hpp>
#include "unit/fns.hpp"
#include "unit/globals.hpp"

using namespace sym;

Module::Module(): name{dt::StrView{"global"}} {
  // Init builtins here
}

const dt::StrView& Module::Name() const noexcept {
  return name;
}

void Module::DefineLocal(dt::StrView name, Type ty) {
  auto local = scope.LocalSymbol(name);

  if (local.IsVoid()) {
    scope.DefineSymbol(name, Type{ty});
  } else {
    throw "local already defined";
  }
}

Type Module::MaybeVoidSymbol(dt::StrView name) {
  auto local = scope.Symbol(name);

  if (local.IsVoid()) {
    return unit::get_global(name);
  } else {
    return local;
  }
}

Type Module::Symbol(dt::StrView name) {
  auto maybe_void = MaybeVoidSymbol(name);

  if (maybe_void.IsVoid()) {
    throw "symbol: unbound var referenced";
  } else {
    return maybe_void;
  }
}

Type Module::SymbolOrFunc(dt::StrView name) {
  auto maybe_void = MaybeVoidSymbol(name);

  if (maybe_void.IsVoid()) {
    // auto multifunc = func_name_map.Find(name);
    auto multi_fn = unit::get_multi_fn(name);

    if (multi_fn) {
      if (1 == multi_fn->funcs.size()) { // Precise type exists
        return multi_fn->funcs.begin()->second->type;
      } else {
        return multi_fn->type;
      }
    } else {
      throw "symbol or func: unbound var referenced";
    }
  } else {
    return maybe_void;
  }
}

Type Module::LocalSymbol(dt::StrView name) {
  return scope.Symbol(name);
}

int Module::LocalsCount() const noexcept {
  return scope.LevelSize();
}

void Module::CreateScopeLevel() {
  scope.CreateLevel();
}

void Module::DropScopeLevel() {
  scope.DropLevel();
}

*/

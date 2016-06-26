#include <frontend/go_cc/common/module.hpp>

#include <unit/scope.hpp>
#include <unit/globals.hpp>
#include <unit/fns.hpp>
#include <err/sym_errors.hpp>

using namespace go_cc;

#include <cstdio>
sym::Type go_cc::get_module_symbol(dt::StrView name) {
  auto scope_symbol = unit::scope_symbol(name);
  if (!scope_symbol.IsVoid()) {
    return scope_symbol;
  }

  auto global = unit::get_global(name);
  if (global) {
    return global->type;
  }

  auto mono_fn = unit::get_mono_fn(name);
  if (mono_fn) {
    return mono_fn->type;
  }

  throw err::UndefinedSymbol{name};
}

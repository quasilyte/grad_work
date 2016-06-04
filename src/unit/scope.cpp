#include "unit/scope.hpp"

#include "sym/scope.hpp"

using namespace unit;

sym::Scope scope;

void unit::create_scope_level() {
  scope.CreateLevel();
}
#include <cstdio>
void unit::drop_scope_level() {
  // printf("%d\n", scope.LevelSize());
  scope.DropLevel();
}

void unit::scope_push(dt::StrView name, sym::Type type) {
  scope.DefineSymbol(name, type);
}

sym::Type unit::scope_symbol(dt::StrView name) {
  return scope.Symbol(name);
}

sym::Type unit::scope_local_symbol(dt::StrView name) {
  return scope.Symbol(name);
}

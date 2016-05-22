#pragma once

#include "dt/str_view.hpp"
#include "dt/dict.hpp"
#include "sym/type.hpp"
#include "sym/fn.hpp"
#include "sym/struct.hpp"
#include "sym/param.hpp"
#include "sym/scope.hpp"

namespace sym {
  class Module;
}

class sym::Module {
public:
  typedef std::vector<ast::Node*> ExprList;

  Module();

  const dt::StrView& Name() const noexcept;

  void CreateScopeLevel();
  void DropScopeLevel();

  // Locals:
  void DefineLocal(dt::StrView name, Type);
  Type LocalSymbol(dt::StrView name);
  int LocalsCount() const noexcept;

  Type MaybeVoidSymbol(dt::StrView name);
  Type Symbol(dt::StrView name);
  Type SymbolOrFunc(dt::StrView name);

private:
  dt::StrView name;

  Scope scope;
};


#pragma once

#include "sym/type.hpp"
#include "dt/str_view.hpp"
#include "sym/param.hpp"
#include <vector>

namespace ast {
  struct Node;
}

namespace sym {
  struct Func;
}

struct sym::Func {
  typedef std::vector<sym::Param> ParamList;
  typedef std::vector<ast::Node*> ExprList;

  Func(dt::StrView name, ParamList&&, ExprList&&, sym::Type);

  int Arity() const noexcept;

  const ParamList& Params() const noexcept;

  dt::StrView name;
  ExprList exprs;
  ParamList params;
  sym::Type ret_type;
  bool variadic = false;
};

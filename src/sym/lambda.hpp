#pragma once

#include "sym/type.hpp"
#include "sym/param.hpp"
#include <vector>

namespace ast {
  struct Node;
}

namespace sym {
  struct Lambda;
}

struct sym::Lambda {
  typedef std::vector<sym::Param> ParamList;
  typedef std::vector<ast::Node*> ExprList;

  Lambda(Type::Id, ParamList&&, sym::Type);
  Lambda(ParamList&&, sym::Type);

  uint Arity() const noexcept;

  const ParamList& Params() const noexcept;

  void Define(ExprList&& exprs, Type ty);

  ExprList exprs;
  ParamList params;
  sym::Type ret_type;
  Type::Id type_id; // Assigned from outside (module/lambda container)
};

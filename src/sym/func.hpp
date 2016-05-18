#pragma once

#include "sym/type.hpp"
#include "dt/str_view.hpp"
#include "sym/param.hpp"
#include <vector>

namespace ast {
  struct Node;
}

namespace sym {
  class Func;
}

class sym::Func {
public:
  Func(std::vector<Param>&& params, std::vector<ast::Node*>&& exprs, sym::Type);

  int Arity() const noexcept;
  const std::vector<Param>& Params() const noexcept;

  std::vector<ast::Node*> exprs;
  Type ret_type;
private:
  std::vector<Param> params;
};

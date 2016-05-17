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
  Func(std::vector<Param>&& params, ast::Node* expr, sym::Type);
  // Func(sym::Type* ret_type, std::vector<sym::Type>&& params);

  int Arity() const noexcept;
  const std::vector<Param>& Params() const noexcept;

  ast::Node* expr;
  Type ret_type;
private:
  std::vector<Param> params;
};

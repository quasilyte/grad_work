#pragma once

#include "sym/type.hpp"
#include "dt/str_view.hpp"
#include "sym/param.hpp"
#include <map>
#include <vector>

namespace ast {
  struct Node;
}

namespace sym {
  struct Func;
  struct MultiFunc;
}

struct sym::MultiFunc {
  typedef std::vector<sym::Type> Key;

  sym::Func* Func(Key);

  uint arity;
  std::map<Key, sym::Func*> funcs;
};

struct sym::Func {
  typedef std::vector<sym::Param> ParamList;
  typedef std::vector<ast::Node*> ExprList;

  Func(dt::StrView name, ParamList&&, sym::Type);

  uint Arity() const noexcept;

  const ParamList& Params() const noexcept;

  void Define(ExprList&& exprs, Type ty);

  const dt::StrView name;
  ExprList exprs;
  ParamList params;
  sym::Type ret_type;
  sym::Type type;
  u32 suffix_idx;
};

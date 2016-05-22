#pragma once

#include "sym/type.hpp"
#include "dt/str_view.hpp"
#include "sym/fn.hpp"
#include <vector>

namespace ast {
  struct Node;
}

namespace sym {
  struct Param;
}

namespace unit {
  typedef std::vector<sym::Param> ParamList;
  typedef std::vector<ast::Node*> ExprList;

  sym::Fn* get_fn(sym::Type ty);

  sym::TypeId new_unnamed_fn(ParamList&&, ExprList&&, sym::Type ret_ty);
  sym::UnnamedFn* get_unnamed_fn(sym::Type id);
  sym::UnnamedFn* get_unnamed_fn(uint idx);
  uint unnamed_fn_count();

  sym::NamedFn* declare_named_fn(dt::StrView name, ParamList&&, const sym::MultiFn::Key&);
  sym::NamedFn* get_named_fn(sym::Type);
  sym::NamedFn* get_named_fn(uint idx);
  uint named_fn_count();

  sym::MultiFn* get_multi_fn(dt::StrView name);
}

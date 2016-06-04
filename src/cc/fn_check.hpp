#pragma once

#include "ast/typedefs.hpp"

namespace sym {
  struct MonoFn;
}

namespace cc {
  void check_arity(sym::MonoFn*, const ast::ArgList&);
  void check_arg_types(sym::MonoFn*, const ast::ArgList&s);
}

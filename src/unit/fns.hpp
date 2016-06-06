#pragma once

#include <ast/typedefs.hpp>
#include <sym/typedefs.hpp>
#include "sym/type.hpp"
#include "dt/str_view.hpp"
#include "sym/fn.hpp"
#include <deps/cxx/vector.hpp>

namespace ast {
  struct Node;
}

namespace sym {
  struct Param;
}

namespace unit {
# define ParamList sym::ParamList
# define NodeList ast::NodeList
# define StrView dt::StrView
# define MultiFn sym::MultiFn

  sym::Fn* get_fn(sym::Type ty);

  sym::Type new_unnamed_fn(ParamList&&, NodeList&&, sym::Type ret_ty);
  sym::UnnamedFn* get_unnamed_fn(sym::Type id);
  sym::UnnamedFn* get_unnamed_fn(uint idx);
  uint unnamed_fn_count();

  sym::NamedFn* declare_named_fn(StrView name, ParamList&&, const MultiFn::Key&);
  sym::NamedFn* get_named_fn(sym::Type);
  sym::NamedFn* get_named_fn(uint idx);
  uint named_fn_count();

  sym::MonoFn* declare_mono_fn(StrView name, ParamList&&, sym::Type ret_type);
  sym::MonoFn* get_mono_fn(StrView name);
  sym::MonoFn* get_mono_fn(sym::Type);
  sym::MonoFn* get_mono_fn(uint idx);
  uint mono_fn_count();

  MultiFn* get_multi_fn(StrView name);
  MultiFn* get_multi_fn(sym::Type);

# undef ParamList
# undef NodeList
# undef StrView
# undef MultiFn
}

#pragma once

#include "ast/typedefs.hpp"
#include "sym/type.hpp"
#include "sym/param.hpp"
#include "sym/typedefs.hpp"
#include <deps/cxx/vector.hpp>
#include <deps/cxx/map.hpp>

namespace sym {
  struct Fn;
  struct UnnamedFn;
  struct NamedFn;
  struct MultiFn;
  struct MonoFn;
}

namespace ast {
  struct Node;
}

namespace sym {
  struct Fn;
}

struct sym::Fn {
  Fn(sym::Type, ParamList&&, ast::NodeList&&, sym::Type ret_type);
  Fn(sym::Type, ParamList&&, sym::Type ret_type);
  Fn(ParamList&&, sym::Type ret_type);

  uint Arity() const noexcept;

  const ParamList& Params() const noexcept;

  ast::NodeList exprs;
  ParamList params;
  sym::Type ret_type;
  sym::Type type;
};

struct sym::MonoFn: public Fn {
  MonoFn(dt::StrView name, ParamList&&, sym::Type ret_type, sym::Type type);

  void Define(ast::NodeList&& exprs);

  dt::StrView name;
};

struct sym::UnnamedFn: public Fn {
  UnnamedFn(sym::Type, ParamList&&, ast::NodeList&&, sym::Type ret_type);
};

struct sym::NamedFn: public Fn {
  NamedFn(ParamList&&, sym::Type ret_ty);
  NamedFn(MultiFn* parent, ParamList&&, sym::Type ret_ty, u32 suffix_idx);

  void Define(ast::NodeList&& exprs, sym::Type ty);

  MultiFn* parent;
  u32 suffix_idx;
};

struct sym::MultiFn {
  typedef std::vector<sym::Type> Key;

  MultiFn(sym::Type, dt::StrView name, uint arity);

  sym::NamedFn* Find(Key);

  const dt::StrView name;
  std::map<Key, sym::NamedFn*> funcs;
  uint arity;
  sym::Type type;
};

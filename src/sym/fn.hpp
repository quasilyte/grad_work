#pragma once

#include "sym/type.hpp"
#include "sym/param.hpp"
#include <vector>
#include <map>

namespace sym {
  struct Fn;
  struct UnnamedFn;
  struct NamedFn;
  struct MultiFn;
}

namespace ast {
  struct Node;
}

namespace sym {
  struct Fn;
}

struct sym::Fn {
  typedef std::vector<sym::Param> ParamList;
  typedef std::vector<ast::Node*> ExprList;

  Fn(sym::TypeId, ParamList&&, ExprList&&, sym::Type ret_type);
  Fn(ParamList&&, sym::Type ret_type);

  uint Arity() const noexcept;

  const ParamList& Params() const noexcept;

  ExprList exprs;
  ParamList params;
  sym::Type ret_type;
  sym::TypeId type_id;
};

struct sym::UnnamedFn: public Fn {
  UnnamedFn(sym::TypeId, ParamList&&, ExprList&&, sym::Type ret_type);
};

struct sym::NamedFn: public Fn {
  NamedFn(ParamList&&, sym::Type ret_ty);
  NamedFn(dt::StrView name, ParamList&&, sym::Type ret_ty, u32 suffix_idx);

  void Define(ExprList&& exprs, sym::Type ty);

  const dt::StrView name;
  u32 suffix_idx;
};

struct sym::MultiFn {
  typedef std::vector<sym::Type> Key;

  MultiFn(uint arity);

  sym::NamedFn* Find(Key);

  uint arity;
  std::map<Key, sym::NamedFn*> funcs;
};

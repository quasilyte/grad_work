#pragma once

#include "sym/type.hpp"
#include "dt/str_view.hpp"
#include "sym/param.hpp"
#include "sym/lambda.hpp"
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

struct sym::Func: public Lambda {
  Func(dt::StrView name, ParamList&&, sym::Type);

  const dt::StrView name;
  u32 suffix_idx; // Assigned from the Module::DeclareFunc
};

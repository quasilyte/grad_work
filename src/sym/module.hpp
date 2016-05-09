#pragma once

#include "dt/str_view.hpp"
#include "dt/dict.hpp"
#include "sym/type.hpp"
#include "sym/func.hpp"
#include "sym/local.hpp"
#include "sym/generator.hpp"

namespace sym {
  class Module;
}

class sym::Module {
public:
  Module(const char* name);

  const dt::StrView& Name() const noexcept;

  // Functions:
  void DefineFunc(dt::StrView name, int arity);
  const sym::Func& Func(dt::StrView name) const;

  // Locals:
  const dt::StrView* DefineLocal(dt::StrView name, const Type*);
  const dt::StrView* RebindLocal(dt::StrView name, const Type*);
  sym::Local Local(dt::StrView name) const;

  // #TODO: globals
  // void MergeSymbol(dt::StrView name, const Type*);

private:
  dt::StrView name;
  mutable dt::Dict<sym::Local> locals;
  mutable dt::Dict<sym::Func> funcs;
  sym::Generator gensym;
  // + globals
};

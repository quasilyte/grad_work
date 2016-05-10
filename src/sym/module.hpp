#pragma once

#include "dt/str_view.hpp"
#include "dt/dict.hpp"
#include "sym/type.hpp"
#include "sym/func.hpp"
#include "sym/local_var.hpp"
#include "sym/generator.hpp"

namespace sym {
  class Module;
}

class sym::Module {
public:
  Module();
  Module(const char* name);

  const dt::StrView& Name() const noexcept;

  void DefineGlobal(dt::StrView name, sym::Type);
  void UpdateGlobal(dt::StrView name, sym::Type);
  Type Global(dt::StrView name) const;

  // Functions:
  // void DefineFunc(dt::StrView name, int arity);
  // const sym::Func& Func(dt::StrView name) const;

  const dt::StrView* DefineLocal(dt::StrView name, Type);
  const dt::StrView* RebindLocal(dt::StrView name, Type);
  sym::LocalVar Local(dt::StrView name) const;

  // #TODO: globals
  // void MergeSymbol(dt::StrView name, const Type*);

private:
  dt::StrView name;
  mutable dt::Dict<sym::Type> globals;
  mutable dt::Dict<sym::LocalVar> locals;
  // mutable dt::Dict<sym::Func> funcs;
  sym::Generator gensym;
  // + globals
};

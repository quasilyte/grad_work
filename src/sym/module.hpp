#pragma once

#include "dt/str_view.hpp"
#include "dt/dict.hpp"
#include "sym/type.hpp"
#include "sym/func.hpp"
#include "sym/local_var.hpp"
#include "sym/struct.hpp"
// #include "sym/generator.hpp"
#include "sym/scope.hpp"

namespace sym {
  class Module;
}

class sym::Module {
public:
  Module();
  Module(const char* name);

  const dt::StrView& Name() const noexcept;

  sym::Type DefineStruct(dt::StrView name, sym::Struct*);
  sym::Struct* Struct(dt::StrView name) const;
  sym::Struct* Struct(sym::Type::Id) const;

  void DefineGlobalSymbol(dt::StrView name, sym::Type*);
  void UpdateGlobalSymbol(dt::StrView name, sym::Type);
  Type* GlobalSymbol(dt::StrView name) const;

  // Functions:
  void CreateScopeLevel();
  void DropScopeLevel();
  void DefineFunc(dt::StrView name, sym::Func*);
  sym::Func* Func(dt::StrView name) const;
  // const sym::Func& Func(dt::StrView name) const;

  Type* DefineLocal(dt::StrView name, Type);
  Type* LocalSymbol(dt::StrView name);

  Type* Symbol(dt::StrView name);
  // void UpdateSymbol(dt::StrView name, sym::Type);

  /*
  const dt::StrView* DefineLocal(dt::StrView name, Type);
  const dt::StrView* RebindLocal(dt::StrView name, Type);
  sym::LocalVar Local(dt::StrView name) const;
  */

  // #TODO: globals
  // void MergeSymbol(dt::StrView name, const Type*);

private:
  dt::StrView name;
  // mutable dt::Dict<sym

  std::vector<sym::Struct*> type_id_map;
  mutable dt::Dict<sym::Struct*> type_name_map;
  mutable dt::Dict<sym::Type*> globals;
  mutable dt::Dict<sym::Func*> funcs;
  Scope scope;

  // mutable dt::Dict<sym::LocalVar> locals;

  // sym::Generator gensym;
};

// symbol lookup rules:
// 1) search inside all nested scopes
// 2) search inside global funcs
// 3) search inside global vars

/*
{
  int x;
  {
    float x;
  }
}
*/

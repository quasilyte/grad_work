#pragma once

#include "dt/str_view.hpp"
#include "dt/dict.hpp"
#include "sym/type.hpp"
#include "sym/func.hpp"
#include "sym/struct.hpp"
#include "sym/param.hpp"
#include "sym/scope.hpp"

namespace sym {
  class Module;
}

class sym::Module {
public:
  typedef std::vector<ast::Node*> ExprList;

  Module();

  const dt::StrView& Name() const noexcept;

  // Types:
  void DefineStruct(dt::StrView name, std::vector<Param>&& attrs);
  sym::Struct* Struct(dt::StrView name) const;
  sym::Struct* Struct(sym::Type::Id) const;

  // Globals:
  void DefineGlobalSymbol(dt::StrView name, sym::Type);
  Type GlobalSymbol(dt::StrView name) const;

  // Functions:
  void CreateScopeLevel();
  void DropScopeLevel();
  void DeclareFunc(dt::StrView name, const sym::MultiFunc::Key&, sym::Func*);
  struct sym::MultiFunc* MultiFunc(dt::StrView name) const;
  struct sym::Func* Func(sym::Type::Id) const;

  // Locals:
  void DefineLocal(dt::StrView name, Type);
  Type LocalSymbol(dt::StrView name);
  int LocalsCount() const noexcept;

  Type Symbol(dt::StrView name);

  auto Funcs() const noexcept -> typename dt::DictIter<sym::MultiFunc*>;

private:
  dt::StrView name;

  std::vector<sym::Struct*> type_id_map;
  std::vector<sym::Func*> func_id_map;
  mutable dt::Dict<sym::Struct*> type_name_map;
  mutable dt::Dict<sym::Type> globals;
  mutable dt::Dict<sym::MultiFunc*> func_name_map;
  Scope scope;
};


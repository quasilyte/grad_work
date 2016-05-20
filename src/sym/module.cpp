#include "sym/module.hpp"

#include <cmath>

using namespace sym;

Module::Module(): name{dt::StrView{"global"}} {
  // Init builtins here
}

const dt::StrView& Module::Name() const noexcept {
  return name;
}

void Module::DefineStruct(dt::StrView name, std::vector<sym::Param>&& attrs) {
  if (type_name_map.Get(name)) {
    throw "redefinition of struct";
  } else {
    auto type_id = Type{type_name_map.Size()};
    auto s = new sym::Struct{name, std::move(attrs), sym::Type{type_id}};
    type_name_map.Put(name, s);
    type_id_map.push_back(s);
  }
}

sym::Struct* Module::Struct(dt::StrView name) const {
  return type_name_map.Get(name);
}

sym::Struct* Module::Struct(Type::Id type_id) const {
  return type_id_map[type_id -  1];
}

void Module::DefineGlobalSymbol(dt::StrView name, Type ty) {
  if (globals.Get(name).IsVoid()) {
    globals.Put(name, ty);
  } else {
    throw "redefinition of global";
  }
}

Type Module::GlobalSymbol(dt::StrView name) const {
  return globals.Get(name);
}

void Module::DefineLocal(dt::StrView name, Type ty) {
  auto local = scope.LocalSymbol(name);

  if (local.IsVoid()) {
    scope.DefineSymbol(name, Type{ty});
  } else {
    throw "local already defined";
  }
}

Type Module::MaybeVoidSymbol(dt::StrView name) {
  auto local = scope.Symbol(name);

  if (local.IsVoid()) {
    return globals.Get(name);
  } else {
    return local;
  }
}

Type Module::Symbol(dt::StrView name) {
  auto maybe_void = MaybeVoidSymbol(name);

  if (maybe_void.IsVoid()) {
    throw "symbol: unbound var referenced";
  } else {
    return maybe_void;
  }
}

Type Module::SymbolOrFunc(dt::StrView name) {
  auto maybe_void = MaybeVoidSymbol(name);

  if (maybe_void.IsVoid()) {
    auto multifunc = func_name_map.Get(name);

    if (multifunc) {
      if (1 == multifunc->funcs.size()) { // Precise type exists
        return multifunc->funcs.begin()->second->type;
      } else {
        throw "symbol or func: duck typing for func not implemented";
      }
    } else {
      throw "symbol or func: unbound var referenced";
    }
  } else {
    return maybe_void;
  }
}

auto Module::Funcs() const noexcept -> dt::DictIter<struct MultiFunc*> {
  return func_name_map.Iter();
}

Type Module::LocalSymbol(dt::StrView name) {
  return scope.Symbol(name);
}

int Module::LocalsCount() const noexcept {
  return scope.LevelSize();
}

void Module::DeclareFunc(dt::StrView name, const sym::MultiFunc::Key& key, sym::Func* func) {
  auto multifunc = func_name_map.Get(name);

  if (multifunc) { // Has at least 1 definition
    if (multifunc->arity != func->Arity()) {
      throw "DeclareFunc: arity mismatch";
    }

    // Has definition with same signature
    auto found_dup = multifunc->funcs.find(key) != multifunc->funcs.end();

    if (found_dup) {
      throw "DeclareFunc: func already defined";
    } else {
      func->suffix_idx = multifunc->funcs.size();
      multifunc->funcs[key] = func;
    }
  } else { // First declaration, no overloadings yet
    multifunc = new sym::MultiFunc{};
    multifunc->arity = func->Arity();
    func->suffix_idx = 0;
    multifunc->funcs[key] = func;

    func_name_map.Put(name, multifunc);
  }

  func->type = Type{-static_cast<Type::Id>(func_id_map.size())};
  func_id_map.push_back(func);
}

MultiFunc* Module::MultiFunc(dt::StrView name) const {
  return func_name_map.Find(name);
}

Func* Module::Func(Type::Id type_id) const {
  return func_id_map[std::abs(type_id)];
}

void Module::CreateScopeLevel() {
  scope.CreateLevel();
}

void Module::DropScopeLevel() {
  scope.DropLevel();
}


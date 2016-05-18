#include "sym/module.hpp"

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

sym::Struct* Module::Struct(sym::Type::Id type_id) const {
  return type_id_map[type_id -  1];
}

void Module::DefineGlobalSymbol(dt::StrView name, Type* ty) {
  if (globals.Get(name)) {
    throw "redefinition of global";
  } else {
    globals.Put(name, ty);
  }
}

void Module::UpdateGlobalSymbol(dt::StrView name, Type ty) {
  auto global = globals.Get(name);

  if (global) {
    global->ExtendWith(ty);
  } else {
    throw "update of undefined global";
  }
}

Type* Module::GlobalSymbol(dt::StrView name) const {
  return globals.Get(name);
}

Type* Module::DefineLocal(dt::StrView name, Type ty) {
  auto local = scope.LocalSymbol(name);

  if (local) {
    throw "local already defined";
  } else {
    return scope.DefineSymbol(name, ty);
  }
}

Type* Module::Symbol(dt::StrView name) {
  auto local = scope.Symbol(name);

  if (local) {
    return local;
  } else {
    auto global = globals.Get(name);
    if (global) {
      return global;
    } else {
      throw "unbound var referenced";
    }
  }
}

Type* Module::LocalSymbol(dt::StrView name) {
  return scope.Symbol(name);
}

void Module::DefineFunc(dt::StrView name, sym::Func* func) {
  funcs.Put(name, func);
}

Func* Module::Func(dt::StrView name) const {
  return funcs.Get(name);
}

void Module::CreateScopeLevel() {
  scope.CreateLevel();
}

void Module::DropScopeLevel() {
  scope.DropLevel();
}


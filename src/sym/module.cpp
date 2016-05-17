#include "sym/module.hpp"

using namespace sym;

Module::Module(): name{dt::StrView{"global"}} {}

Module::Module(const char *name): name{dt::StrView{name}} {}

const dt::StrView& Module::Name() const noexcept {
  return name;
}


Type Module::DefineStruct(dt::StrView name, sym::Struct* s) {
  if (type_name_map.Get(name)) {
    throw "redefinition of struct";
  } else {
    auto type_id = Type{type_name_map.Size()};
    type_name_map.Put(name, s);
    type_id_map.push_back(s);
    return type_id;
  }
}

sym::Struct* Module::Struct(dt::StrView name) const {
  return type_name_map.Get(name);
}

sym::Struct* Module::Struct(sym::Type::Id type_id) const {
  return type_id_map[type_id];
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

/*
void Module::UpdateSymbol(dt::StrView name, Type ty) {
  auto local = scope.Symbol(name);
}
*/

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

/*
const dt::StrView* Module::DefineLocal(dt::StrView name, Type ty) {
  if (locals.Get(name).type.IsVoid()) {
    auto interned_name = gensym.Next();
    locals.Put(name, sym::LocalVar{ty, interned_name});
    return interned_name;
  } else {
    throw "already defined";
  }
}

const dt::StrView* Module::RebindLocal(dt::StrView name, Type ty) {
  auto local = locals.Get(name);

  if (local.type.IsVoid()) {
    throw "rebind of undefined";
  } else {
    auto new_name = gensym.Next();
    locals.Put(name, sym::LocalVar{ty, new_name});
    return new_name;
  }
}
*/

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

/*
#include "dbg/dt.hpp"
#include "sym/sym.hpp"

using namespace sym;

Module::Module(const char *name): name{dt::StrView{name}} {}

void Module::DefineFunc(dt::StrView name, int arity) {
  // if (funcs.Get(name))
  funcs.Put(name, sym::Func{arity});
}

const dt::StrView* Module::DefineLocal(dt::StrView name, const Type* type) {
  if (nullptr == locals.Get(name).type) {
    auto interned_name = gensym.Next();
    locals.Put(name, sym::LocalVar{type, interned_name});
    return interned_name;
  } else {
    throw "already defined";
  }
}

void Module::MergeSymbol(dt::StrView name, const Type* type) {
  auto symbol = locals.Get(name);

  if (nullptr == symbol.type) {
    throw "update of undefined";
  } else {
    // locals.Put(name, sym::Local{name, symbol.type->Merge(type)});
  }
}

const dt::StrView* Module::RebindLocal(dt::StrView name, const Type* type) {
  auto local = locals.Get(name);

  if (nullptr == local.type) {
    throw "rebind of undefined";
  } else {
    auto new_name = gensym.Next();
    locals.Put(name, sym::LocalVar{type, new_name});
    return new_name;
  }
}

sym::LocalVar Module::Local(dt::StrView name) const {
  return locals.Get(name);
}

const sym::Func& Module::Func(dt::StrView name) const {
  return funcs.Get(name);
}

const dt::StrView& Module::Name() const noexcept {
  return name;
}
*/

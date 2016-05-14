#include "sym/module.hpp"

using namespace sym;

Module::Module(): name{dt::StrView{"global"}} {}

Module::Module(const char *name): name{dt::StrView{name}} {}

const dt::StrView& Module::Name() const noexcept {
  return name;
}

const Type* Module::Symbol(dt::StrView name) {
  //  return
}

void Module::DefineGlobal(dt::StrView name, Type ty) {
  if (globals.Get(name).IsVoid()) {
    globals.Put(name, ty);
  } else {
    throw "redefinition of global";
  }
}

void Module::UpdateGlobal(dt::StrView name, Type ty) {
  auto& global = globals.GetMut(name);

  if (global.IsVoid()) {
    throw "update of undefined global";
  } else {
    global.ExtendWith(ty);
  }
}

Type Module::Global(dt::StrView name) const {
  return globals.Get(name);
}

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

sym::LocalVar Module::Local(dt::StrView name) const {
  return locals.Get(name);
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

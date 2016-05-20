#include "sym/func.hpp"

using namespace sym;
using std::vector;

Param::Param(dt::StrView name, Type type): name{name}, type{type} {}

Func* MultiFunc::Func(Key key) {
  auto it = funcs.find(key);

  if (it == funcs.end()) {
    return nullptr;
  } else {
    return it->second;
  }
}

Func::Func(dt::StrView name, ParamList&& params, Type ty):
name{name}, params{params}, ret_type{ty} {}

uint Func::Arity() const noexcept {
  return params.size();
}

const Func::ParamList& Func::Params() const noexcept {
  return params;
}

void Func::Define(ExprList &&exprs, Type ty) {
  ret_type = ty;
  this->exprs = exprs;
}

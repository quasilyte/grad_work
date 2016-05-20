#include "sym/func.hpp"

using namespace sym;
using std::vector;

Param::Param(dt::StrView name, Type type): name{name}, type{type} {}

Func::Func(dt::StrView name, ParamList&& params, Type ty):
name{name}, params{params}, ret_type{ty} {}

int Func::Arity() const noexcept {
  return params.size();
}

const Func::ParamList& Func::Params() const noexcept {
  return params;
}

void Func::Define(ExprList &&exprs, Type ty) {
  ret_type = ty;
  this->exprs = exprs;
}

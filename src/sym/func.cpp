#include "sym/func.hpp"

using namespace sym;
using std::vector;

Param::Param(dt::StrView name, Type type): name{name}, type{type} {}

Func::Func(dt::StrView name, ParamList&& params, ExprList&& exprs, Type ty):
name{name}, exprs{exprs}, ret_type{ty}, params{params} {}

int Func::Arity() const noexcept {
  return params.size();
}

const Func::ParamList& Func::Params() const noexcept {
  return params;
}

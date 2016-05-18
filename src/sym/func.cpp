#include "sym/func.hpp"

using namespace sym;

Param::Param(dt::StrView name, Type type): name{name}, type{type} {}

Func::Func(std::vector<Param>&& params, std::vector<ast::Node*>&& exprs, Type ty):
exprs{exprs}, ret_type{ty}, params{params} {}

int Func::Arity() const noexcept {
  return params.size();
}

const std::vector<Param>& Func::Params() const noexcept {
  return params;
}

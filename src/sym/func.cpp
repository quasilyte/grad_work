#include "sym/func.hpp"

using namespace sym;

Param::Param(dt::StrView name, Type type): name{name}, type{type} {}

Func::Func(std::vector<Param>&& params, ast::Node* expr, Type ty):
expr{expr}, ret_type{ty}, params{params} {}

/*
Func::Func(Type* ret_type, std::vector<Type>&& params):
ret_type{ret_type}, params{params} {}
*/

int Func::Arity() const noexcept {
  return params.size();
}

const std::vector<Param>& Func::Params() const noexcept {
  return params;
}

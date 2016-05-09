#include "sym/func.hpp"

using namespace sym;

Func::Func(int arity) {
  params.reserve(arity);
}

Func::Func(Type* ret_type, std::vector<Type*>&& params):
ret_type{ret_type}, params{params} {}

int Func::Arity() const noexcept {
  return params.size();
}

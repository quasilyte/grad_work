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
Lambda{std::move(params), ty}, name{name} {}

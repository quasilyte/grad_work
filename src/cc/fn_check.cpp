#include <cc/fn_check.hpp>

#include <sym/fn.hpp>
#include <err/fn_errors.hpp>
#include <ast/node.hpp>

void cc::check_arity(sym::MonoFn* fn, uint arg_count) {
  if (arg_count != fn->Arity()) {
    throw err::FnCallArity{fn->name, fn, arg_count};
  }
}

void cc::check_arg_types(sym::MonoFn* fn, const ast::ArgList& args) {
  for (uint i = 0; i < fn->params.size(); ++i) {
    auto arg_type = args[i]->Type();
    auto param = fn->params[i];

    if (!arg_type.SameAs(param.type)) {
      throw err::FnCallArgType{fn->name, param, arg_type};
    }
  }
}

#include <cc/fn_check.hpp>

#include <typedefs.hpp>
#include <sym/fn.hpp>
#include <errors.hpp>
#include <ast/node.hpp>

void cc::check_arity(sym::MonoFn* fn, const ast::ArgList& args) {
  if (args.size() != fn->Arity()) {
    throw err::FnCallArity{fn->name, fn, static_cast<uint>(args.size())};
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

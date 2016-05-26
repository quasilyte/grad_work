#include "backend/cpp/cg/utils.hpp"

#include "backend/cpp/cg/type_map.hpp"
#include "sym/module.hpp"
#include "sym/sym.hpp"
#include "di/pipe.hpp"
#include "io/file_writer.hpp"
#include "intrinsic/type_ops.hpp"
#include "cc/translation_unit.hpp"
#include "backend/cpp/cg/code_writer.hpp"
#include "unit/fns.hpp"
#include "unit/structs.hpp"

using namespace sym;
using namespace dt;
using namespace di;

Type deep_ret_type(Fn* lambda) {
  while (lambda->ret_type.IsFn()) {
    lambda = unit::get_fn(lambda->ret_type);
  }

  return lambda->ret_type;
}

void cpp_cg::write_type(const cc::TranslationUnit& tu, Type ty) {
  if (ty.IsStruct()) {
    get_pipe()("struct ")(unit::get_struct(ty)->name);
  } else if (ty.IsFn()) {
    Fn* lambda = unit::get_fn(ty);

    write_type(tu, deep_ret_type(lambda));
  } else {
    get_pipe()(type_name(ty));
  }
}

void cpp_cg::write_func_name(const NamedFn* f) {
  get_pipe()(f->parent->name)(gen_suffix(f->suffix_idx));
}

void cpp_cg::write_lambda_name(const Fn* l) {
  get_pipe()('l')(gen_suffix(l->type.Id()));
}

void cpp_cg::write_named_params(const cc::TranslationUnit& tu, const Fn::ParamList& params) {
  if (params.size()) {
    get_pipe()('(');
    for (uint i = 0; i < params.size() - 1; ++i) {
      write_type(tu, params[i].type);
      get_pipe()(' ')(params[i].name)(',');
    }
    write_type(tu, params.back().type);
    get_pipe()(' ')(params.back().name);
    get_pipe()(')');
  } else {
    get_pipe()("(void)");
  }
}

void cpp_cg::write_params(const cc::TranslationUnit& tu, const Fn::ParamList& params) {
  if (params.size()) {
    get_pipe()('(');
    for (uint i = 0; i < params.size() - 1; ++i) {
      write_type(tu, params[i].type);
      get_pipe()(',');
    }
    write_type(tu, params.back().type);
    get_pipe()(')');
  } else {
    get_pipe()("(void)");
  }
}

void cpp_cg::write_intrinsic_params(Type ty) {
  auto arity = intrinsic::arity_of(ty);

  if (arity) {
    get_pipe()('(');
    for (uint i = 0; i < arity - 1; ++i) {
      get_pipe()(type_name(intrinsic::param_of(ty, i)))(',');
    }
    get_pipe()(type_name(intrinsic::param_of(ty, arity - 1)))(')');
  } else {
    get_pipe()("(void)");
  }
}

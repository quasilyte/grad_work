#include "backend/cpp/cg/utils.hpp"

#include "backend/cpp/cg/type_map.hpp"
#include "sym/module.hpp"
#include "sym/func.hpp"
#include "sym/lambda.hpp"
#include "sym/sym.hpp"
#include "di/output.hpp"
#include "io/file_writer.hpp"

using namespace sym;
using namespace di;

void cpp_cg::write_type(const Module* mod, Type ty) {
  if (ty.IsStruct()) {
    module_writer()("struct ", 7)(mod->Struct(ty.Tag())->name);
  } else {
    module_writer()(type_name(ty));
  }
}

void cpp_cg::write_func_name(const Func* f) {
  module_writer()(f->name)(gen_suffix(f->suffix_idx));
}

void cpp_cg::write_lambda_name(const Lambda* l) {
  module_writer()('l')(gen_suffix(Type::LambdaKey(l->type_id)));
}

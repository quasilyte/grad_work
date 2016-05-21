#include "backend/cpp/cg/utils.hpp"

#include "backend/cpp/cg/type_map.hpp"
#include "sym/module.hpp"
#include "sym/func.hpp"
#include "sym/lambda.hpp"
#include "sym/sym.hpp"
#include "di/output.hpp"

using namespace sym;
using namespace di;

void cpp_cg::write_type(const Module* mod, Type ty) {
  if (ty.IsStruct()) {
    module_write("struct ", 7);
    module_write(mod->Struct(ty.Tag())->name);
  } else {
    module_write(type_name(ty));
  }
}

void cpp_cg::write_func_name(const Func* f) {
  module_write(f->name);
  module_write(gen_suffix(f->suffix_idx));
}

void cpp_cg::write_lambda_name(const Lambda* l) {
  module_write('l');
  module_write(gen_suffix(Type::LambdaKey(l->type_id)));
}

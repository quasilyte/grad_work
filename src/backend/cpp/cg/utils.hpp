#pragma once

#include "sym/lambda.hpp"

namespace sym {
  class Module;
  class Type;
  struct Func;
}

namespace cc {
  struct TranslationUnit;
}

namespace cpp_cg {
  using namespace sym;
  using namespace dt;

  void write_type(const cc::TranslationUnit& tu, Type);

  void write_func_name(const Func*);
  void write_lambda_name(const Lambda*);
  void write_named_params(const cc::TranslationUnit& tu, const Lambda::ParamList&);
  void write_params(const cc::TranslationUnit& tu, const Lambda::ParamList&);
  void write_intrinsic_params(Type);
}


#pragma once

#include "sym/fn.hpp"

namespace sym {
  class Module;
  class Type;
  struct NamedFn;
}

namespace cc {
  struct TranslationUnit;
}

namespace cpp_cg {
  using namespace sym;
  using namespace dt;

  void write_type(const cc::TranslationUnit& tu, Type);

  void write_func_name(const sym::NamedFn*);
  void write_lambda_name(const Fn*);
  void write_named_params(const cc::TranslationUnit& tu, const Fn::ParamList&);
  void write_params(const cc::TranslationUnit& tu, const Fn::ParamList&);
  void write_intrinsic_params(Type);
}


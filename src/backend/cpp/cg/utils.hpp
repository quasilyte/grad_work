#pragma once

namespace sym {
  class Module;
  class Type;
  struct Func;
  struct Lambda;
}

namespace cpp_cg {
  void write_type(const sym::Module*, sym::Type);
  void write_func_name(const sym::Func*);
  void write_lambda_name(const sym::Lambda*);
}

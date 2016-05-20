#pragma once

namespace io {
  class FileWriter;
}

namespace sym {
  class Module;
  class Type;
  struct Func;
}

namespace cpp_cg {
  void write_type(const sym::Module*, sym::Type, const io::FileWriter*);
  void write_func_name(const sym::Func*, const io::FileWriter*);
}

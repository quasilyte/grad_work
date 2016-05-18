#pragma once

namespace io {
  class FileWriter;
}

namespace sym {
  class Module;
  class Type;
}

namespace cpp_cg {
  void write_type(const sym::Module*, sym::Type, const io::FileWriter*);
}

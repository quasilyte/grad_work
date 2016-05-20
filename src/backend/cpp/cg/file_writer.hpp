#pragma once

namespace io {
  class FileWriter;
}

namespace cpp_cg {
  struct FileWriter;
}

struct cpp_cg::FileWriter {
  const io::FileWriter& runtime;
  const io::FileWriter& module;
};

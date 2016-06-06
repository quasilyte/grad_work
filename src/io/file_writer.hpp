#pragma once

#include <deps/c/stdio.hpp>
#include "typedefs.hpp"

namespace io {
  class FileWriter;
}

namespace dt {
  class StrView;
}

class io::FileWriter {
public:
  FileWriter();
  FileWriter(FILE*);

  void SetFile(FILE*);

  void Close();

  FileWriter operator()(char);
  FileWriter operator()(const char*, u32 amount);
  FileWriter operator()(const dt::StrView&);

private:
  FILE* file;
};

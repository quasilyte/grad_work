#pragma once

#include "typedefs.hpp"
#include <cstdio>

namespace io {
  class FileWriter;
}

class io::FileWriter {
public:
  struct FileNotFound{};

  FileWriter();
  FileWriter(const char *file_path);
  ~FileWriter();

  void write(char);
  void write(const char *cstr);
  void write(const char *bytes, u32 len);

  void close();

private:
  FILE *file = nullptr;
};

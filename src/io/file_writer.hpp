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

  void Write(char) const;
  void Write(const char *cstr) const ;
  void Write(const char *bytes, u32 len) const;

  void Close();

private:
  FILE *file = nullptr;
};

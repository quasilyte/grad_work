#pragma once

#include "typedefs.hpp"
#include "dt/str_view.hpp"
#include <cstdio> // #FIXME: can not forward declare FILE* :(

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
  void Write(const dt::StrView&) const;
  // void WriteMangled(const dt::StrView&) const;

  void Close();

private:
  FILE *file = nullptr;
};

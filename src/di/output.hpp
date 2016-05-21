#pragma once

#include <cstdio>
#include "dt/str_view.hpp"

namespace di {
  void set_files(FILE* module, FILE* runtime);
  void close_files();

  void module_write(const dt::StrView&);
  void module_write(const char* bytes, u32 amount);
  void module_write(char);
  void runtime_write(const dt::StrView&);
  void runtime_write(const char* bytes, u32 amount);
  void runtime_write(char);
}

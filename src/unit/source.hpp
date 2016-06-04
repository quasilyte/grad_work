#pragma once

#include "typedefs.hpp"

namespace unit {
  int get_line_number(const char* location);
  int get_error_count();

  void set_source_root(const char* root);
}

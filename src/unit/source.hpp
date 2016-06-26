#pragma once

#include <typedefs.hpp>
#include <dt/str_view.hpp>

namespace lex {
  struct Cursor;
}

namespace unit {
  int get_line_number(dt::StrView);
  int get_line_number(const char* location);

  int get_error_count();

  void set_source_root(const char* root);
}

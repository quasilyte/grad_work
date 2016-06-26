#include <unit/source.hpp>

const char* last_location = nullptr;
int line_number = 1;
int error_count = 0;

int unit::get_line_number(dt::StrView str_view) {
  return get_line_number(str_view.Data());
}

int unit::get_line_number(const char *location) {
  for (const char* p = last_location; p < location; ++p) {
    if ('\n' == *p) {
      line_number += 1;
    }
  }

  last_location = location;
  error_count += 1;
  return line_number;
}

int unit::get_error_count() {
  return error_count;
}

void unit::set_source_root(const char *root) {
  last_location = root;
}

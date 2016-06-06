#include <sym/rules.hpp>

#include <dt/str_view.hpp>

bool sym::is_type_name(const dt::StrView& s) {
  return s[0] >= 'A' && s[0] <= 'Z';
}

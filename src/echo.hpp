#pragma once

#include "dt/str_view.hpp"
#include <deps/c/stdio.hpp>
#include <deps/c/stdlib.hpp>

namespace echo {
  [[ noreturn ]] void error(const char* fmt, dt::StrView a1);
}

void echo::error(const char *fmt, dt::StrView a1) {
  std::fprintf(stderr, fmt, a1.Len(), a1.Data());
  exit(1);
}

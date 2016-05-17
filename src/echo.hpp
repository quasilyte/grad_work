#pragma once

#include "dt/str_view.hpp"
#include <cstdio>
#include <cstdlib>

namespace echo {
  [[ noreturn ]] void error(const char* fmt, dt::StrView a1);
}

void echo::error(const char *fmt, dt::StrView a1) {
  std::fprintf(stderr, fmt, a1.Len(), a1.Data());
  exit(1);
}

/*
void WriteFormatted ( const char * format, ... )
{
  va_list args;
  va_start (args, format);
  vprintf (format, args);
  va_end (args);
}

int main ()
{
   WriteFormatted ("Call with %d variable argument.\n",1);
   WriteFormatted ("Call with %d variable %s.\n",2,"arguments");

   return 0;
}
*/

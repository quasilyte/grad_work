#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef int64_t Int_;
typedef double Real_;
typedef _Bool Bool_;

inline Int_ int_Int_(Int_ x) { return x; }
inline Int_ int_Real_(Real_ x) { return (Int_)x; }

inline Real_ real_Real_(Real_ x) { return x; }
inline Real_ real_Int_(Int_ x) { return (Real_)x; }

__attribute__ ((noreturn))
void error(const char* msg)  {
  puts(msg);
  exit(1);
}

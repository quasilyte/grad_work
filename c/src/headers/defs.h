#ifndef HEADERS_DEFS_
#define HEADERS_DEFS_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define deftype(name) \
  typedef struct name name; \
  struct name

typedef size_t size;
typedef intptr_t ptr;
typedef uintptr_t uptr;
typedef ptrdiff_t index;

#endif

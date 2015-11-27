#ifndef HEADERS_BUF_
#define HEADERS_BUF_

#include <string.h>

#include "defs.h"

deftype(Buf) {
  size cap;
  char* mem;
};

Buf buf_new(size cap);
void buf_free(Buf* self);

#endif

#include "buf.h"

#include <stdlib.h>

Buf buf_new(size cap) {
  return (Buf) {
    .cap = cap,
    .mem = malloc(cap)
  };
}

void buf_free(Buf* self) {
  free(self->mem);
}

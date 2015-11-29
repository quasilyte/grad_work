#ifndef HEADERS_ARR_
#define HEADERS_ARR_

#include <string.h>

#include "defs.h"

// Array is an abstraction on top of the
// raw pointer. It owns typed memory segment
// of knowed size.
// It also provides checked indexing access.
deftype(Arr) {
  size cap;
  char* mem;
};

Arr arr_new(size cap);
void arr_realloc(Arr* self, size cap);
void arr_free(Arr* self);

inline bool is_null(const Arr* self);

/**
 * Inline functions: 
 */

inline bool is_null(const Arr* self) {
  return NULL == self->mem;
}

#endif

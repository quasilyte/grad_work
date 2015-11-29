#ifndef HEADERS_VEC_
#define HEADERS_VEC_

#include "arr.h"

// Vector is a growable vecay
deftype(Vec) {
  // size len;
  char* restrict current;
  Arr arr;
};

inline Vec vec_new(size cap);
// Vec vec_new(size cap);
void vec_free(Vec* self);

inline char vec_pop(Vec* self);
inline void vec_push(Vec* self, const char elt);

// void vec_push(Vec* self, char elt);

/**
 * Inline functions: 
 */

inline char vec_pop(Vec* self) {  
  return *--self->current;
}

inline void vec_push(Vec* self, const char elt) {  
  ++self->current;
}

inline Vec vec_new(size cap) {
  if (cap < 32) {
    cap = 32;
  }
  
  Arr arr = arr_new(cap); 
  
  return (Vec) {
    // .len = 0,
    .current = arr.mem,
    .arr = arr
  };
}

#endif

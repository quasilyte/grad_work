#pragma once

#include <stdlib.h>
#include <assert.h>

/**
 * Default implementation generators for trivial cases
 * like array of chars (char*) or array of ints (int*).
 * More generally, it can handle flat arrays of types
 * those do not require calling some cleanup functions.
 * So, user defined type like Point is OK too
 */

#define ARR_NEW(ID, PREFIX, T)				\
  ID PREFIX##_new(size_t cap) {				\
    T* mem = malloc(cap *  sizeof(T));			\
    assert(mem != NULL);				\
    return (ID) {					\
      .cap = cap,					\
      .mem = mem					\
    };   						\
  }
	    
#define ARR_REALLOC(ID, PREFIX, T)				      \
  void PREFIX##_realloc(ID* self, size_t cap) {			      \
    T* new_mem = realloc(self->mem, cap * sizeof(T));		      \
    assert(new_mem != NULL);					      \
    self->mem = new_mem;					      \
    self->cap = cap;						      \
  }

#define ARR_FREE(ID, PREFIX, T)				\
  void PREFIX##_free(ID* self) {			\
    assert(self->mem != NULL);				\
    free(self->mem);					\
    self->mem = NULL;					\
  }

#define ARR_IMPL(ID, PREFIX, T)		\
  ARR_NEW(ID, PREFIX, T)		\
  ARR_REALLOC(ID, PREFIX, T)		\
  ARR_FREE(ID, PREFIX, T)

#endif

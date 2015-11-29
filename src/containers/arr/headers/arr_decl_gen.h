#pragma once

#include <stddef.h>
#include <stdbool.h>

#define ARR_DECL(ID, PREFIX, ELEM_TYPE)			\
  typedef struct ID ID;					\
  struct ID {						\
    size_t cap;						\
    ELEM_TYPE* mem;					\
  };							\
							\
  ID PREFIX##_new(size_t cap);				\
  void PREFIX##_realloc(ID* self, size_t cap);		\
  void PREFIX##_free(ID* self);				\
							\
  inline bool PREFIX##_is_null(const ID* self);		\
							\
  /* Inline functions implementation */			\
							\
  inline bool PREFIX##_is_null(const ID* self) {       	\
    return NULL == self->mem;				\
  } 

#pragma once

#include "arr/headers/arr.h"
#include <assert.h>

#define VEC_DECL(ID, PREFIX, ARR_T, ELT_T)				\
  typedef struct ID ID;							\
  struct ID {								\
    size_t len;								\
    ARR_T arr;								\
  };									\
									\
  ID PREFIX##_new(size_t cap);						\
  void PREFIX##_free(ID* self);						\
									\
  static inline void PREFIX##_wild_push(ID* self, ELT_T elt);		\
  static inline void PREFIX##_push(ID* self, ELT_T elt);		\
  static inline ELT_T PREFIX##_wild_pop(ID* self);			\
  static inline ELT_T PREFIX##_pop(ID* self);				\
									\
  /* Static Inline functions implementation */				\
									\
  static inline void PREFIX##_wild_push(ID* self, ELT_T elt) {		\
    self->arr.mem[self->len++] = elt;					\
  }									\
									\
  static inline void PREFIX##_push(ID* self, ELT_T elt) {		\
    if (self->len == self->arr.cap) {					\
      arr_realloc(&self->arr, self->arr.cap * 2);			\
    }									\
    PREFIX##_wild_push(self, elt);					\
  }									\
									\
  static inline ELT_T PREFIX##_wild_pop(ID* self) {			\
    return self->arr.mem[--self->len];					\
  }									\
									\
  static inline ELT_T PREFIX##_pop(ID* self) {				\
    assert(0 != self->len);						\
    return PREFIX##_wild_pop(self);					\
  }

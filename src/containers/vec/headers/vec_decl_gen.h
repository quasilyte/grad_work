#pragma once

#include "arr.h"
#include <assert.h>

#define ELT_T(ID) __typeof__(*(((ID*) 0)->arr.mem))

#define VEC_DECL(ID, PREFIX, ARR_T)					 \
  typedef struct ID ID;							 \
  struct ID {								 \
    size_t len;								 \
    ARR_T arr;								 \
  };									 \
									 \
  ID PREFIX##_new(size_t cap);						 \
  void PREFIX##_free(ID* self);						 \
									 \
  static inline void PREFIX##_wild_push(ID *self, ELT_T(ID) elt);        \
  static inline void PREFIX##_push(ID *self, ELT_T(ID) elt);	         \
  void PREFIX##_npush_arr(ID* self, ARR_T *arr, size_t n);		 \
  void PREFIX##_push_arr(ID *self, ARR_T *arr);				 \
  void PREFIX##_push_vec(ID *self, ID *vec);				 \
  static inline ELT_T(ID) PREFIX##_wild_pop(ID *self);		         \
  static inline ELT_T(ID) PREFIX##_pop(ID *self);                        \
									 \
  /* Static Inline functions implementation */				 \
  									 \
  static inline void PREFIX##_wild_push(ID* self, ELT_T(ID) elt) {       \
    self->arr.mem[self->len++] = elt;					 \
  }									 \
									 \
  static inline void PREFIX##_push(ID* self, ELT_T(ID) elt) {	         \
    if (self->len == self->arr.cap) {					 \
      arr_enlarge(&self->arr);						 \
    }									 \
    PREFIX##_wild_push(self, elt);					 \
  }									 \
									 \
  static inline ELT_T(ID) PREFIX##_wild_pop(ID* self) {		         \
    return self->arr.mem[--self->len];					 \
  }									 \
									 \
  static inline ELT_T(ID) PREFIX##_pop(ID* self) {			 \
    assert(0 != self->len);						 \
    return PREFIX##_wild_pop(self);					 \
  }

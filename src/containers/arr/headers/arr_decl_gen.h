#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define ARR_DECL(ID, PREFIX, ELT_T)					\
  typedef struct ID ID;							\
  struct ID {								\
    size_t cap;								\
    ELT_T* mem;								\
  };									\
									\
  static inline ID PREFIX##_new(size_t cap);				\
  static inline void PREFIX##_init(ID* self, size_t cap);		\
  void PREFIX##_realloc(ID* self, size_t cap);				\
  void PREFIX##_enlarge(ID* self);					\
  static inline void PREFIX##_free(ID* self);				\
									\
  static inline bool PREFIX##_is_null(const ID* self);			\
									\
  static inline void PREFIX##_ensure_cap(ID* self, size_t cap);		\
									\
  /* Inline functions implementation */					\
									\
  static inline ID PREFIX##_new(size_t cap) {				\
    ELT_T* mem = malloc(cap * sizeof(ELT_T));				\
    assert(mem != NULL);						\
    return (ID) {							\
      .cap = cap,							\
      .mem = mem							\
    };  								\
  }									\
									\
  static inline void PREFIX##_init(ID* self, size_t cap) {		\
    ELT_T* mem = malloc(cap * sizeof(ELT_T));				\
    assert(NULL != mem);						\
    self->mem = mem;							\
    self->cap = cap;							\
  }									\
									\
  static inline void PREFIX##_free(ID* self) {				\
    assert(self->mem != NULL);						\
    free(self->mem);							\
    self->mem = NULL;							\
  }									\
									\
  static inline void PREFIX##_ensure_cap(ID *self, size_t cap) {	\
    if (self->cap < cap ) {						\
      PREFIX##_realloc(self, cap + (cap >> 1));				\
    }									\
  }									\
									\
  static inline bool PREFIX##_is_null(const ID* self) {			\
    return NULL == self->mem;						\
  }									\


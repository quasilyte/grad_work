#pragma once

#include <stddef.h>
#include <stdbool.h>

#define ARR_DECL(ID, PREFIX, ELT_T)			\
  typedef struct ID ID;					\
  struct ID {						\
    size_t cap;						\
    ELT_T* mem;						\
  };							\
							\
  ID PREFIX##_new(size_t cap);				\
  void PREFIX##_init(ID* self, size_t cap);		\
  void PREFIX##_realloc(ID* self, size_t cap);		\
  void PREFIX##_enlarge(ID* self);			\
  void PREFIX##_ensure_cap(ID* self, size_t cap);	\
  void PREFIX##_free(ID* self);				\
							\
  static inline bool PREFIX##_is_null(const ID* self);	\
							\
  /* Inline functions implementation */			\
							\
  static inline bool PREFIX##_is_null(const ID* self) {	\
    return NULL == self->mem;				\
  } 

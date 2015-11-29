#pragma once

/**
 * Default implementation generators for trivial cases
 * like array of chars (char*) or array of ints (int*).
 * More generally, it can handle flat arrays of types
 * those do not require calling some cleanup functions.
 * So, user defined type like Point is OK too
 */

#define ARR_REALLOC(ID, PREFIX, ELT_T)				\
  void PREFIX##_realloc(ID* self, size_t cap) {			\
    ELT_T* new_mem = realloc(self->mem, cap * sizeof(ELT_T));	\
    assert(new_mem != NULL);					\
    self->mem = new_mem;					\
    self->cap = cap;						\
  }

#define ARR_ENLARGE(ID, PREFIX, ELT_T)					\
  void PREFIX##_enlarge(ID *self) {					\
    self->cap <<= 1;							\
    ELT_T* new_mem = realloc(self->mem, self->cap * sizeof(ELT_T));	\
    assert(NULL != new_mem);						\
    self->mem = new_mem;						\
  }

#define ARR_IMPL(ID, PREFIX, ELT_T)		\
  ARR_REALLOC(ID, PREFIX, ELT_T)		\
  ARR_ENLARGE(ID, PREFIX, ELT_T)		

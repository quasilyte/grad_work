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

#define ARR_NEW(ID, PREFIX, ELT_T)			\
  ID PREFIX##_new(size_t cap) {				\
    ELT_T* mem = malloc(cap * sizeof(ELT_T));		\
    assert(mem != NULL);				\
    return (ID) {					\
      .cap = cap,					\
      .mem = mem					\
    };   						\
  }

#define ARR_INIT(ID, PREFIX, ELT_T)		\
  void PREFIX##_init(ID* self, size_t cap) {	\
    ELT_T* mem = malloc(cap * sizeof(ELT_T));	\
    assert(NULL != mem);			\
    self->mem = mem;				\
    self->cap = cap;				\
  }    

#define ARR_REALLOC(ID, PREFIX, ELT_T)				      \
  void PREFIX##_realloc(ID* self, size_t cap) {			      \
    ELT_T* new_mem = realloc(self->mem, cap * sizeof(ELT_T));	      \
    assert(new_mem != NULL);					      \
    self->mem = new_mem;					      \
    self->cap = cap;						      \
  }

#define ARR_ENLARGE(ID, PREFIX, ELT_T)					\
  void PREFIX##_enlarge(ID *self) {					\
    self->cap <<= 1;							\
    ELT_T* new_mem = realloc(self->mem, self->cap * sizeof(ELT_T));	\
    assert(NULL != new_mem);						\
    self->mem = new_mem;						\
  }

#define ARR_ENSURE_CAP(ID, PREFIX)		   \
  void PREFIX##_ensure_cap(ID *self, size_t cap) { \
    if (self->cap < cap ) {			   \
      PREFIX##_realloc(self, cap + (cap >> 1));	   \
    }						   \
  }

#define ARR_FREE(ID, PREFIX, ELT_T)			\
  void PREFIX##_free(ID* self) {			\
    assert(self->mem != NULL);				\
    free(self->mem);					\
    self->mem = NULL;					\
  }

#define ARR_IMPL(ID, PREFIX, ELT_T)		\
  ARR_NEW(ID, PREFIX, ELT_T)			\
  ARR_INIT(ID, PREFIX, ELT_T)			\
  ARR_REALLOC(ID, PREFIX, ELT_T)		\
  ARR_ENLARGE(ID, PREFIX, ELT_T)		\
  ARR_ENSURE_CAP(ID, PREFIX)			\
  ARR_FREE(ID, PREFIX, ELT_T)

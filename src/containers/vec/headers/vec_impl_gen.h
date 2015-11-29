#pragma once

#include "arr.h"
#include <stdio.h>
#include <string.h>

#define VEC_NEW(ID, PREFIX, ARR_T)		\
  ID PREFIX##_new(size_t cap) {			\
    ARR_T arr;					\
    arr_init(&arr, cap);			\
    return (ID) {				\
      .len = 0,					\
      .arr = arr,				\
    };  					\
  }

#define VEC_NPUSH_ARR(ID, PREFIX, ARR_T)			\
  void PREFIX##_npush_arr(ID* self, ARR_T* arr, size_t n) {	\
    arr_ensure_cap(&self->arr, self->len + n);			\
    size_t byte_size = n * sizeof(*(arr->mem));			\
    memcpy(self->arr.mem + self->len, arr->mem, byte_size);	\
    self->len += n;						\
  }

#define VEC_PUSH_ARR(ID, PREFIX, ARR_T)					\
  void PREFIX##_push_arr(ID* self, ARR_T* arr) {			\
    PREFIX##_npush_arr(self, arr, arr->cap);				\
  }

#define VEC_PUSH_VEC(ID, PREFIX)					\
  void PREFIX##_push_vec(ID* self, ID* vec) {				\
    PREFIX##_npush_arr(self, &vec->arr, vec->len);			\
  }

#define VEC_FREE(ID, PREFIX)			\
  void PREFIX##_free(ID* self) {		\
    arr_free(&self->arr);			\
  }

#define VEC_IMPL(ID, PREFIX, ARR_T)		\
  VEC_NEW(ID, PREFIX, ARR_T)			\
  VEC_NPUSH_ARR(ID, PREFIX, ARR_T)		\
  VEC_PUSH_ARR(ID, PREFIX, ARR_T)		\
  VEC_PUSH_VEC(ID, PREFIX)			\
  VEC_FREE(ID, PREFIX)				


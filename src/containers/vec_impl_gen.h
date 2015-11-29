#pragma once

#include "arr/headers/arr.h"

#define VEC_NEW(ID, PREFIX, ARR_T)		\
  ID PREFIX##_new(size_t cap) {			\
    ARR_T arr;					\
    arr_init(&arr, cap);			\
    return (ID) {				\
      .len = 0,					\
      .arr = arr,				\
    };  					\
  }

#define VEC_FREE(ID, PREFIX)			\
  void PREFIX##_free(ID* self) {		\
    arr_free(&self->arr);			\
  }

#define VEC_IMPL(ID, PREFIX, ARR_T)		\
  VEC_NEW(ID, PREFIX, ARR_T)			\
  VEC_FREE(ID, PREFIX)				\
  

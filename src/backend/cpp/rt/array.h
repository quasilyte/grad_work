#pragma once

#include "core.h"

struct ArrayHandle_Int_ {
  Int_ id;
};

struct Array_Int_ {
  Int_ len;
  Int_* elems;
};

#define MAX_ARRAY_INT_ 2
struct Array_Int_ Arrays_Int_[MAX_ARRAY_INT_];

static inline struct ArrayHandle_Int_
new_Array_Int_(Int_ len) {
  for (Int_ i = 0; i < MAX_ARRAY_INT_; ++i) {
    struct Array_Int_* arr = (Arrays_Int_ + i);

    if (NULL == arr->elems) {
      arr->elems = malloc(sizeof(Int_) * len);
      arr->len = len;
      return (struct ArrayHandle_Int_){i};
    }
  }

  error("no more slots");
}

static inline Int_
len_Array_Int_(struct ArrayHandle_Int_ arr) {
  return Arrays_Int_[arr.id].len;
}

static inline Int_
nth_Array_Int_(struct ArrayHandle_Int_ arr, Int_ idx) {
  return Arrays_Int_[arr.id].elems[idx];
}

static inline void
set_Array_Int_(struct ArrayHandle_Int_ arr, Int_ idx, Int_ val) {
  Arrays_Int_[arr.id].elems[idx] = val;
}

#pragma once

#include "char_vec.h"
#include "int_vec.h"

#define VEC_VARIANTS(FN_NAME) \
  CharVec*: vecc_##FN_NAME, \
  IntVec*: veci_##FN_NAME

#define VEC_GENERIC1(FN_NAME, SELF)			\
  _Generic((SELF), VEC_VARIANTS(FN_NAME))((SELF))
#define VEC_GENERIC2(FN_NAME, SELF, PARAM1)			\
  _Generic((SELF), VEC_VARIANTS(FN_NAME))((SELF), (PARAM1))

#define vec_free(SELF) VEC_GENERIC1(free, SELF)
#define vec_wild_push(SELF, ELT) VEC_GENERIC2(wild_push, SELF, ELT)
#define vec_push(SELF, ELT) VEC_GENERIC2(push, SELF, ELT)
#define vec_push_arr(SELF, ARR) VEC_GENERIC2(push_arr, SELF, ARR)
#define vec_push_vec(SELF, VEC) VEC_GENERIC2(push_vec, SELF, VEC)
#define vec_wild_pop(SELF) VEC_GENERIC1(wild_pop, SELF)
#define vec_pop(SELF) VEC_GENERIC1(pop, SELF)



#pragma once

#include "char_arr.h"
#include "int_arr.h"

#define ARR_VARIANTS(FN_NAME) \
  CharArr*: arrc_##FN_NAME, \
  IntArr*: arri_##FN_NAME

#define ARR_GENERIC1(FN_NAME, SELF)			\
  _Generic((SELF), ARR_VARIANTS(FN_NAME))((SELF))
#define ARR_GENERIC2(FN_NAME, SELF, PARAM1)			\
  _Generic((SELF), ARR_VARIANTS(FN_NAME))((SELF), (PARAM1))

#define arr_init(SELF, CAP) ARR_GENERIC2(init, SELF, CAP)
#define arr_realloc(SELF, CAP) ARR_GENERIC2(realloc, SELF, CAP)
#define arr_enlarge(SELF) ARR_GENERIC1(enlarge, SELF)
#define arr_ensure_cap(SELF, CAP) ARR_GENERIC2(ensure_cap, SELF, CAP)
#define arr_free(SELF) ARR_GENERIC1(free, SELF)

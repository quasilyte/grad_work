#pragma once

#include "char_vec.h"
#include "int_vec.h"

#define vec_free(vec)					\
  _Generic((vec),					\
    CharVec*: vecc_free,				\
    IntVec*: veci_free	        			\
  )((vec))

#define vec_wild_push(vec, elt)				\
  _Generic((vec),					\
    CharVec*: vecc_wild_push,				\
    IntVec*: veci_wild_push		        	\
  )((vec), (elt))

#define vec_push(vec, elt)				\
  _Generic((vec),					\
    CharVec*: vecc_push,				\
    IntVec*: veci_push		                	\
  )((vec), (elt))

#define vec_push_arr(vec, arr)				\
  _Generic((vec),					\
    CharVec*: vecc_push_arr,				\
    IntVec*: veci_push_arr			        \
  )((vec), (arr))

#define vec_wild_pop(vec)				\
  _Generic((vec),					\
    CharVec*: vecc_wild_pop,				\
    IntVec*: veci_wild_pop			        \
  )((vec))

#define vec_pop(vec)					\
  _Generic((vec),					\
    CharVec*: vecc_pop,	         			\
    IntVec*: veci_pop   			        \
  )((vec))



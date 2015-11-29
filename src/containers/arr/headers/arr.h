#pragma once

#include "char_arr.h"
#include "int_arr.h"

#define arr_free(arr)			\
  _Generic((arr),			\
    CharArr*: arrc_free,		\
    IntArr*: arri_free			\
  )((arr))

#define arr_realloc(arr, cap)		\
  _Generic((arr),			\
    CharArr*: arrc_realloc,		\
    IntArr*: arri_realloc	        \
  )((arr), (cap))

/*
#define arrc_foreach(arr, induct)		\
  for (char *induct = arr.mem,			\
	      *last = arr.mem + arr.cap;	\
       induct != last; ++induct)			
*/

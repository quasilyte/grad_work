#pragma once

#include "char_arr.h"
#include "int_arr.h"

#define arr_free(ARR)			\
  _Generic((ARR),			\
    CharArr*: arrc_free,		\
    IntArr*: arri_free			\
  )((ARR))

#define arr_realloc(ARR, CAP)		\
  _Generic((ARR),			\
    CharArr*: arrc_realloc,		\
    IntArr*: arri_realloc	        \
  )((ARR), (CAP))

#define arr_init(ARR, CAP)			\
  _Generic((ARR),				\
    CharArr*: arrc_init,			\
    IntArr*: arri_init				\
  )((ARR), (CAP))  

#define arr_enlarge(ARR)		\
  _Generic((ARR),			\
    CharArr*: arrc_enlarge,		\
    IntArr*: arri_enlarge	        \
  )((ARR))

#define arr_ensure_cap(ARR, CAP)	\
  _Generic((ARR),			\
    CharArr*: arrc_ensure_cap,		\
    IntArr*: arri_ensure_cap	        \
  )((ARR), (CAP))

/*
#define arrc_foreach(ARR, induct)		\
  for (char *induct = ARR.mem,			\
	      *last = ARR.mem + ARR.cap;	\
       induct != last; ++induct)			
*/

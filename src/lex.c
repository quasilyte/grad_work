#include "lex.h"

#include <ctype.h>

#define SKIP_WHILE(cond) \
  while (cond) {	 \
    ++self->pos;	 \
  }

inline static void skip_space(Lex* self) {
  SKIP_WHILE(isspace(*self->pos));
}

inline Lex lex_make(Buf input) {
  Lex self = {
    .pos = input.mem,
    .max_pos = input.mem + input.cap,
    .src = input.mem  
  };

  skip_space(&self);
  self.byte = *self.pos;

  return self;
}


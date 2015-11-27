#ifndef HEADERS_LEX_
#define HEADERS_LEX_

#include "defs.h"
#include "buf.h"
#include "tok.h"

deftype(Lex) {
  char byte; 
  char* pos;
  const char* const max_pos;
  char* const src;
};

Lex lex_make(Buf input);

bool lex_has_more(const Lex* lex);
void lex_fetch_into(Lex* lex, Tok* tok);

#endif

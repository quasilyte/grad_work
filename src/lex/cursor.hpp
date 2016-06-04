#pragma once

#include "lex/token.hpp"
#include "dt/str_view.hpp"

namespace lex {
  struct Cursor;

  Cursor* skip(Cursor*, const int* to_skip);
  Cursor* skip(Cursor*, int n);
  Cursor* skip_until(Cursor*, char);

  dt::StrView read(Cursor*, const int* to_read);
  dt::StrView read(Cursor*, void(*scan)(Cursor*));
  dt::StrView read_until(Cursor*, char);
  char read_next(Cursor*);

  Token read_token(Cursor*, u32(*tokenize)(Cursor*));

  dt::StrView read_group(Cursor*, char open_close);
  dt::StrView read_group(Cursor*, char open, char close);

  u64 read_m9(Cursor*, const int* to_read);

  char at(const Cursor*);
  char peek(const Cursor*);

  bool can_read(const Cursor*);

  bool try_consume(Cursor*, char);
  bool try_consume(Cursor*, const char*);
  int try_consume(Cursor*, const int* to_consume);

  int line_number(const Cursor*);
}

struct lex::Cursor {
  const char* pos;
  const char* pos_max;

  Cursor(dt::StrView input);
};

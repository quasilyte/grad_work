#pragma once

#include "dt/str_view.hpp"

namespace lex {
  struct Cursor;
}

namespace go_cc {
  dt::StrView next_ident(lex::Cursor*);
  dt::StrView next_expr(lex::Cursor*);
}

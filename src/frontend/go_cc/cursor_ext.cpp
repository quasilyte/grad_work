#include "frontend/go_cc/cursor_ext.hpp"

#include "lex/cursor.hpp"
#include "frontend/go_cc/char_groups.hpp"

using namespace go_cc;
using namespace lex;

void input_consumer(Cursor* cur) {
  for (;;) {
    switch (at(cur)) {
    case ';':
    case '\n': return;
    case '"': skip(skip_until(skip(cur, 1), '"'), 1); break;
    case '/':
      if ('*' == peek(cur)) {
        skip(cur, 2);
        do {
          skip(skip_until(cur, '*'), 1);
        } while ('/' != at(cur));
      }
    default: skip(cur, 1);
    }
  }
}

dt::StrView go_cc::next_ident(Cursor* cur) {
  return read(skip(cur, SPACES), IDENT);
}

dt::StrView go_cc::next_expr(Cursor* cur) {
  dt::StrView expr_s;

  if ('(' == at(skip(cur, SPACES))) {
    expr_s = read_group(cur, '(', ')');
  } else {
    expr_s = read(cur, input_consumer);
  }

  return expr_s;
}

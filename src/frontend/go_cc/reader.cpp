#include <frontend/go_cc/reader.hpp>

/*
#include <lex/char_case.hpp>
#include <frontend/go_cc/char_groups.hpp>

using namespace go_cc;

void input_consumer(lex::Reader* rd) {
  for (;;) {
    switch (rd->At()) {
    case ';':
    case '\n': return;
    case '"': rd->Skip(1)->SkipUntil('"')->Skip(1); break;
    case '/':
      if ('*' == rd->Peek()) {
        rd->Skip(2);
        do {
          rd->SkipUntil('*')->Skip(1);
        } while ('/' != rd->At());
      }
    default: rd->Skip(1);
    }
  }
}

dt::StrView Reader::NextExpr() {
  dt::StrView expr_s;

  if ('(' == Skip(SPACES)->At()) {
    expr_s = ReadGroup('(', ')').Truncate(1);
  } else {
    expr_s = Read(input_consumer);
  }

  return expr_s;
}

dt::StrView Reader::NextIdent() {
  return Skip(SPACES)->Read(IDENT);
}
*/

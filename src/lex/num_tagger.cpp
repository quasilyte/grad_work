#include <lex/num_tagger.hpp>

#include <lex/char_groups.hpp>
#include <lex/cursor.hpp>

using namespace lex;

u32 NumTagger::Run(lex::Cursor* cur) {
  if (!try_consume(cur, DIGITS)) {
    return MALFORMED;
  }

  if (try_consume(cur, '.')) {
    return try_consume(cur, DIGITS) ? REAL : MALFORMED;
  } else {
    return INT;
  }
}

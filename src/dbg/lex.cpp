#include "dbg/lex.hpp"

#include "lex/token_stream.hpp"
#include <cstdio>
#include <cstdlib>

using namespace lex;

void dump_one_token(Token tok, const char* type, int depth) {
  std::printf("%*s%s `%.*s`\n", depth, "", type, tok.get_len(), tok.get_val());
}

void dbg::dump_token(Token tok, int depth) {

  switch (tok.get_tag()) {
  case Token::INT: dump_one_token(tok, "int", depth); break;
  case Token::REAL: dump_one_token(tok, "real", depth); break;
  case Token::STR: dump_one_token(tok, "str", depth); break;
  case Token::WORD: dump_one_token(tok, "word", depth); break;
  case Token::LIST: {
    std::printf("%*slist(\n", depth, "");
    TokenStream toks{tok};
    while (toks.next_tag() != Token::SOURCE_END) {
      dump_token(toks.current_token(), depth + 1);
    }
    std::printf("%*s)\n", depth, "");
    break;
  }
  case Token::SOURCE_END: std::printf("%*s<EOF>\n", depth, ""); break;

  default:
    printf("unknown tag: %d!\n", tok.get_tag());
    abort();
  }
}


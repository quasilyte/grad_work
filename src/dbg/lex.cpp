#include "dbg/lex.hpp"

#include "lex/token_stream.hpp"
#include <cstdio>
#include <cstdlib>

using namespace lex;

void dump_one_token(Token tok, const char* type, int depth) {
  std::printf("%*s%s `%.*s`\n", depth, "", type, tok.Len(), tok.Val());
}

void dbg::dump_token(Token tok, int depth) {

  switch (tok.Tag()) {
  case Token::INT: dump_one_token(tok, "int", depth); break;
  case Token::REAL: dump_one_token(tok, "real", depth); break;
  case Token::STR: dump_one_token(tok, "str", depth); break;
  case Token::WORD: dump_one_token(tok, "word", depth); break;
  case Token::LIST: {
    std::printf("%*slist(\n", depth, "");
    TokenStream toks{tok};
    while (toks.NextTag() != Token::SOURCE_END) {
      dump_token(toks.CurrentToken(), depth + 1);
    }
    std::printf("%*s)\n", depth, "");
    break;
  }
  case Token::SOURCE_END: std::printf("%*s<EOF>\n", depth, ""); break;

  default:
    printf("unknown tag: %d!\n", tok.Tag());
    abort();
  }
}


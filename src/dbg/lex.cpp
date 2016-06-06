#include <dbg/lex.hpp>

/*
#include <lex/token.hpp>
#include <lex/reader.hpp>
#include <dt/str_view.hpp>
#include <lex/char_type.hpp>
#include <lex/char_case.hpp>
#include <deps/c/stdio.hpp>
#include <deps/c/stdlib.hpp>

using namespace lex;

void dump_one_token(Token tok, const char* type, int depth) {
  std::printf("%*s%s `%.*s`\n", depth, "", type, tok.Len(), tok.Data());
}

void dump_one_token(dt::StrView tok, const char* type, int depth) {
  std::printf("%*s%s `%.*s`\n", depth, "", type, tok.Len(), tok.Data());
}

void dump_tokens
(const int* to_skip, const int* ident, char open, char close, lex::Reader& rd, int depth) {
  std::printf("%*s%c\n", depth, "", open);
  dbg::dump(to_skip, ident, rd.Skip(to_skip)->ReadGroup(open, close), depth + 1);
  std::printf("%*s%c\n", depth, "", close);
}

void dump_term(const char* text, int depth) {
  std::printf("%*s%s\n", depth, "", text);
}

void dbg::dump(const int* to_skip, const int* ident, lex::Reader rd, int depth) {
  while (rd.CanRead()) {
    rd.Skip(to_skip);
    switch (rd.At()) {
    case DIGIT_RANGE: dump_one_token(rd.Skip(to_skip)->ReadReal(), "num", depth); break;
    case '(': dump_tokens(to_skip, ident, '(', ')', rd, depth); break;
    case '[': dump_tokens(to_skip, ident, '[', ']', rd, depth); break;
    case '{': dump_tokens(to_skip, ident, '{', '}', rd, depth); break;
    case '"': dump_one_token(rd.Skip(to_skip)->ReadStr(), "str", depth); break;
    case ',': dump_term("<COMMA>", depth); break;

    default:
      auto tok = rd.Skip(to_skip)->Read(ident);
      if (tok.Len()) {
        dump_one_token(tok, "ident", depth);
      } else {
        throw "unexpected token";
      }
    } 
  }
}

void dbg::dump(Token tok, int depth) {
  switch (tok.Tag()) {
  case Token::INT: dump_one_token(tok, "int", depth); break;
  case Token::REAL: dump_one_token(tok, "real", depth); break;
  case Token::STR: dump_one_token(tok, "str", depth); break;
  case Token::WORD: dump_one_token(tok, "word", depth); break;
  case Token::LIST: {
    std::printf("%*slist(\n", depth, "");
    TokenStream toks{tok};
    while (toks.NextTag() != Token::SOURCE_END) {
      dump(toks.CurrentToken(), depth + 1);
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
*/

#pragma once

#include "typedefs.hpp"
#include "token.hpp"

namespace compiler {
  class Lexer {
  public:
    Lexer(char *input, size_t len);

    bool has_next() const {
      return pos < max_pos;
    }

    Token next();
    
  private:
    char *pos;
    char *max_pos;
    char fetched_byte;

    void skip_spaces();
    void fetch_byte();
    void fetch_word(Token *token);
    void fetch_num(Token *token);
    void fetch_op(Token *token);
  };
}


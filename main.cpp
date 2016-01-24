#include "lexer/token.hpp"
#include "lexer/char_type.hpp"
#include "lexer/token_stream.hpp"
#include "dbg/dump.hpp"
#include "dbg/io.hpp"

#include <cstdio>

int main() {
  auto input = slurp("../Resembler/input/lua/arith.lua");
  TokenStream tokens(input.c_str());

  printf("Input:\n`%s`\n", input.c_str());

  while (tokens.next_tag() != SOURCE_END) {
    dump_token(tokens.current());
  }

  return 0;
}

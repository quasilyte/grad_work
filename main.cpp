#include "runtime/core/types.hpp"
#include "runtime/opt/sum_type.hpp"
#include "lexer/token.hpp"
#include "lexer/char_type.hpp"
#include "lexer/token_stream.hpp"
#include "dbg/dump.hpp"
#include "dbg/io.hpp"
#include "m_hash.hpp"

#include <cstdio>
#include <vector>

int main() {
  // auto input = slurp("../Resembler/input/lua/arith.lua");

  /*
  std::string input{"14 (x y {z 4.6}) [bar()]"};
  printf("Input:\n`%s`\n", input.c_str());

  TokenStream tokens{input.c_str(), input.length()};

  while (tokens.next_tag() != SOURCE_END) {
    dump_token(tokens.current());
  }
  */

  Any a(10L);
  Any b(5.5);
  printf("%f\n", add(b, a).get_real());

  return 0;
}

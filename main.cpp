#include "runtime/core/types.hpp"
#include "runtime/opt/sum_type.hpp"
#include "lexer/token.hpp"
#include "lexer/char_type.hpp"
#include "lexer/token_stream.hpp"
#include "ast/nodes.hpp"
#include "dbg/dump.hpp"
#include "dbg/io.hpp"
#include "m_hash.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

int main() {
  // auto input = slurp("../Resembler/input/lua/arith.lua");

  /*
  std::string input{"14 (x \"hello !!\" {z 4.6}) [bar()]"};
  printf("Input:\n`%s`\n", input.c_str());
  TokenStream tokens{input.c_str(), input.length()};
  while (tokens.next_tag() != SOURCE_END) {
    dump_token(tokens.current());
  }
  */

  std::string output;

  auto ast = new Ast::Fn{
    Token{WORD, "hello"},
    Token{WORD, "x"}, std::vector<Ast::Node*> {
      new Ast::Decimal{Token{DECIMAL, "5422"}},
      new Ast::String{Token{STR, "hello, world!"}},
      new Ast::Return{
        new Ast::Sum{
          new Ast::Real{Token{REAL, "6.3"}},
          new Ast::Decimal{Token{DECIMAL, "5649"}}
        }
      }
    }
  };
  ast->write(output);

  printf("%s\n", output.c_str());

  return 0;
}

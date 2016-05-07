#include <cstring>
#include <cstdio>
#include "lex/token.hpp"
#include "lex/token_stream.hpp"
#include "dbg/lex.hpp"
#include "dbg/dt.hpp"
#include "cc/parser.hpp"
#include "cc/code_gen.hpp"
#include "io/file_writer.hpp"
#include "sym/type.hpp"
#include "ast/node.hpp"
#include "dt/dict.hpp"
#include <fstream>
#include <string>

std::string slurp(const char* path) {
  std::ifstream input{path};
  return std::string(
    std::istreambuf_iterator<char>{input},
    std::istreambuf_iterator<char>{}
  );
}

// +: 1~n args (each <- numeric)
// 1) called with apply -- expand to real function
// 2) stored in variable -- expand to real function
// 3) called inline -- series or "+"

// (module "main")
// (def (sum a b) (+ a b))
// (sum 4.5 6.0) (; type error)
// (set-type! sum (int a b))

// phases & passes:
// pass[1] (parser):
// + build the ast
// - maintain symbol table
// - estimate types
// pass[2]:
// - type check
// + generate code

// int main(int argc, char* argv[]) {
int main() {
  using namespace lex;

  try {
    // const char* input = "(#type x real)(define x 10.5)";
    const char* input = "(define x (if 1 2.2 3.2))(set! x 10.0)";
    // const char* input = "(define x (if 1 15 3)) (set! x 10)";
    // const char* input = "(define x (if 1 15 3)) (#type x int)";
    io::FileWriter fw{};
    cc::Parser parser{input};
    auto parse_tree = parser.Parse();
    cc::CodeGen cg{parser.Module(), parse_tree};
    cg.WriteTo(fw);
  } catch (const char* msg) {
    std::fprintf(stderr, "error: %s\n", msg);
  }

  /*
  try {
    std::string input = slurp(argv[1]);
    if (input.size()) {
      // const char* input = "(define x (if 1 1 0)) (set! x 10)";
      io::FileWriter fw{};
      cc::Parser parser{input.c_str()};
      cc::CodeGen cg{parser.parse()};
      cg.write_to(&fw);
    } else {
      throw "file not found";
    }
  } catch (const char* msg) {
    std::fprintf(stderr, "error: %s\n", msg);
  }
  */

  return 0;
}

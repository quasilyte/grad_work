#include <cstring>
#include <cstdio>
#include "lex/token.hpp"
#include "lex/token_stream.hpp"
#include "dbg/lex.hpp"
#include "cc/parser.hpp"
#include "cc/code_gen.hpp"
#include "io/file_writer.hpp"
#include "sym/type.hpp"
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
// pass[1]:
// + build the ast
// - maintain symbol table
// - estimate types
// pass[2]:
// - type check
// + generate code

int main(int argc, char* argv[]) {
  using namespace lex;

  try {
    const char* input = "(define x (if 1 15 0.3)) (set! x 10)";
    io::FileWriter fw{};
    cc::Parser parser{input};
    auto parse_tree = parser.parse();
    cc::CodeGen cg{parse_tree};
    cg.write_to(&fw);
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

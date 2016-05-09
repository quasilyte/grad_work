#include <cstring>
#include <cstdio>
#include "lex/token.hpp"
#include "lex/token_stream.hpp"
#include "dbg/lex.hpp"
#include "dbg/dt.hpp"
#include "cc/parser.hpp"
#include "cc/code_gen.hpp"
#include "io/file_writer.hpp"
#include "sym/generator.hpp"
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

// 1_zeros => 10
// 2_zeros => 100


// +: 1~n args (each <- numeric)
// 1) called with apply -- expand to real function
// 2) stored in variable -- expand to real function
// 3) called inline -- series or "+"
#include <limits>
// int main(int argc, char* argv[]) {
int main() {
  using namespace lex;

  // lookup по одному и тому же имени
  //
  try {
    const char* input = R"lisp(
        (#;
        (def (f x y) 1.6)
        (def res (f 1 2)))

        (def x (if 1 1 1.0))
        (def y (+ x 1))

        (#;(def x 10) (#; [x: int])
        (set! x 10.0)
        (set! x 1)
        (def y x))

    )lisp";

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
      cc::CodeGen cg{parser.Module(), parser.Parse()};
      cg.WriteTo(fw);
    } else {
      throw "file not found";
    }
  } catch (const char* msg) {
    std::fprintf(stderr, "error: %s\n", msg);
  }
  */

  return 0;
}

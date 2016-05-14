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
#include "cc/classifier.hpp"
#include "dt/dict.hpp"
#include "ast/atoms.hpp"
#include "ast/defs.hpp"
#include "backend/cpp/cg/visitor.hpp"
#include "backend/cpp/cg/translator.hpp"
#include "ast/builtins.hpp"
#include <fstream>
#include <string>
#include "dt/alist.hpp"

std::string slurp(const char* path) {
  std::ifstream input{path};
  return std::string(
    std::istreambuf_iterator<char>{input},
    std::istreambuf_iterator<char>{}
  );
}

// 16 + 4

// +: 1~n args (each <- numeric)
// 1) called with apply -- expand to real function
// 2) stored in variable -- expand to real function
// 3) called inline -- series or "+"

// int main(int argc, char* argv[]) {
int main() {
  using namespace lex;
  using namespace cc;
  using namespace cpp_cg;

  try {
    const char* input = R"lisp(
        (#; testing)
        (#def x (if 1 1 1.0))
        (#def y x)
    )lisp";

    Translator::Run(Parser::Run(Classifier::Run(input)));
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

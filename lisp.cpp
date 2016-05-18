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
#include "backend/cpp/cg/code_writer.hpp"
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

struct Foo: public ast::Node {
  dt::StrView* name;
  std::vector<ast::Node*> args;
  // sym::Type ty;
};

// quote can yield:
// * symbol
// * self-quoting value (int, real, etc.)
// * list of quoted values (symbols, ints, etc.)
// so, basically, the only "magical" value is symbol.
// also, quote of quote is, of course, results in list
// which car is "quote".

// (and x y) -> either<x, y>
// (or x y) -> either<x, y>
// (< x y) -> int
// (= x y) -> int

// int main(int argc, char* argv[]) {
int main() {
  using namespace lex;
  using namespace cc;
  using namespace cpp_cg;
  printf("%ld\n", sizeof(sym::Func));
  try {
    const char* input =
        R"lisp(
        (#def y (if 1 1 1.0))
        (#def x (- 1 3 5))

    )lisp";

    Translator::Run(Parser::Run(Classifier::Run(input)));
    // Parser::Run(Classifier::Run(input));
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

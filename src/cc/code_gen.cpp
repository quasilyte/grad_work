#include "cc/code_gen.hpp"

#include "ast/node.hpp"

using namespace cc;

CodeGen::CodeGen(const Parser::Tree& tree): tree{tree} {}

void CodeGen::write_to(io::FileWriter* fw) {
  for (ast::Node* node : tree) {
    node->generate_code(fw);
  }
}

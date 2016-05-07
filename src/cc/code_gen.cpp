#include "cc/code_gen.hpp"

#include "ast/node.hpp"

using namespace cc;

CodeGen::CodeGen(const Parser::Tree& tree): tree{tree} {}

void CodeGen::WriteTo(const io::FileWriter& fw) {
  for (ast::Node* node : tree) {
    node->GenerateCode(fw);
  }
}

#include "cc/code_gen.hpp"

#include "ast/node.hpp"

using namespace cc;

CodeGen::CodeGen(const sym::Module& module, const Parser::Tree& tree):
module{module}, tree{tree} {}

void CodeGen::WriteTo(const io::FileWriter& fw) {
  for (ast::Node* node : tree) {
    node->GenerateCode(module, fw);
    fw.Write('\n');
  }
}

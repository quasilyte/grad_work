#include "cc/code_gen.hpp"

#include "ast/node.hpp"

/*
using namespace cpp_cg;

void CodeGen::Run(const cc::TranslationUnit& input, const io::FileWriter& output) {
  CodeGen self{input, output};
  return self.Generate();
}

CodeGen::CodeGen(const cc::TranslationUnit& tu, const io::FileWriter& fw):
tu{tu}, fw{fw} {}

void CodeGen::Generate() {
  for (ast::Node* node : tu.tree) {
    node->GenerateCode(tu.module, fw);
    fw.Write('\n');
  }
}
*/

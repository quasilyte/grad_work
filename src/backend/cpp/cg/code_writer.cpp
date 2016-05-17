#include "backend/cpp/cg/code_writer.hpp"

#include "ast/node.hpp"
#include "ast/defs.hpp"
#include "ast/builtins.hpp"
#include "ast/atoms.hpp"
#include "ast/cond.hpp"
#include "sym/module.hpp"
#include "sym/struct.hpp"
#include "backend/cpp/cg/type_map.hpp"

#include <cstdio>

using namespace cpp_cg;

void CodeWriter::Run(ast::Node* node, const sym::Module& module, const io::FileWriter& fw) {
  CodeWriter self{module, fw};
  self.Visit(node);
}

CodeWriter::CodeWriter(const sym::Module& module, const io::FileWriter& fw):
module{module}, fw{fw} {}

void CodeWriter::Visit(ast::Node* node) {
  node->Accept(this);
}

void CodeWriter::Visit(ast::Int* node) {
  fw.Write(node->datum);
}

void CodeWriter::Visit(ast::Real* node) {
  fw.Write(node->datum);
}

void CodeWriter::Visit(ast::Str* node) {
  fw.Write(node->datum);
}

void CodeWriter::Visit(ast::Sym* node) {
  // fw.Write(node->datum);
  fw.Write("SYM", 3);
}

void CodeWriter::Visit(ast::Sum* node) {
  auto operands = node->operands;
  for (uint i = 0; i < operands.size() - 1; ++i) {
    operands[i]->Accept(this);
    fw.Write('+');
  }
  operands.back()->Accept(this);
}

void CodeWriter::Visit(ast::SetVar* node) {
  fw.Write(node->name);
  fw.Write('=');
  node->value->Accept(this);
  fw.Write(';');
}

void CodeWriter::Visit(ast::DefVar* node) {
  if (node->type->IsStruct()) {
    fw.Write("struct ", 7);
    fw.Write(module.Struct(node->type->Tag())->name);
  } else {
    fw.Write(type_name(node->type));
  }
  fw.Write(' ');
  fw.Write(node->name);
  fw.Write('=');
  node->value->Accept(this);
  fw.Write(';');
}

void CodeWriter::Visit(ast::If* node) {
  fw.Write("(");
  node->cond->Accept(this);
  fw.Write(")?(");
  node->on_true->Accept(this);
  fw.Write("):(");
  node->on_false->Accept(this);
  fw.Write(")");
}

void CodeWriter::Visit(ast::Var* node) {
  fw.Write(node->name);
}

void CodeWriter::Visit(ast::FuncCall* node) {
  fw.Write(node->name);
  fw.Write('(');
  for (uint i = 0; i < node->args.size() - 1; ++i) {
    node->args[i]->Accept(this);
    fw.Write(',');
  }
  node->args.back()->Accept(this);
  fw.Write(')');
}

void CodeWriter::Visit(ast::CompoundLiteral* node) {
  sym::Struct* s = module.Struct(node->type.Tag());

  fw.Write("(struct ", 8);
  fw.Write(s->name);
  fw.Write("){", 2);
  for (uint i = 0; i < node->initializers.size() - 1; ++i) {
    node->initializers[i]->Accept(this);
    fw.Write(',');
  }
  node->initializers.back()->Accept(this);
  fw.Write('}');
}

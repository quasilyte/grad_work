#include "backend/cpp/cg/visitor.hpp"

#include "ast/node.hpp"
#include "ast/defs.hpp"
#include "ast/builtins.hpp"
#include "ast/atoms.hpp"
#include "backend/cpp/cg/type_map.hpp"

#include <cstdio>

using namespace cpp_cg;

void Visitor::Run(ast::Node* node, const io::FileWriter& fw) {
  Visitor self{fw};
  self.Visit(node);
}

Visitor::Visitor(const io::FileWriter& fw): fw{fw} {}

void Visitor::Visit(ast::Node* node) {
  node->Accept(this);
}

void Visitor::Visit(ast::Int* node) {
  fw.Write(node->Data(), node->Len());
}

void Visitor::Visit(ast::Real* node) {
  fw.Write(node->Data(), node->Len());
}

void Visitor::Visit(ast::Str* node) {
  fw.Write(node->Data(), node->Len());
}

void Visitor::Visit(ast::Sum* node) {
  auto operands = node->Operands();
  for (uint i = 0; i < operands.size() - 1; ++i) {
    operands[i]->Accept(this);
    fw.Write('+');
  }
  operands.back()->Accept(this);
}

void Visitor::Visit(ast::SetGlobal* node) {
  fw.Write(node->Name());
  fw.Write('=');
  node->Value()->Accept(this);
  fw.Write(';');
}

void Visitor::Visit(ast::DefLocal* node) {
  fw.Write(type_name(node->Type()));
  fw.Write(' ');
  fw.Write(*node->Name());
  fw.Write('{');
  node->Value()->Accept(this);
  fw.Write('}');
  fw.Write(';');
}

#include "backend/cpp/cg/code_writer.hpp"

#include "ast/node.hpp"
#include "ast/defs.hpp"
#include "ast/builtins.hpp"
#include "ast/atoms.hpp"
#include "ast/cond.hpp"
#include "sym/module.hpp"
#include "sym/struct.hpp"
#include "backend/cpp/cg/type_map.hpp"
#include "backend/cpp/cg/utils.hpp"

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

void CodeWriter::Visit(ast::Sym*) {
  fw.Write("SYM", 3);
}

void CodeWriter::Visit(ast::Sum* node) {
  VisitGroupedList('+', node->operands);
}

void CodeWriter::Visit(ast::Sub* node) {
  VisitGroupedList('-', node->operands);
}

void CodeWriter::Visit(ast::Lt* node) {
  VisitGroupedList('<', node->operands);
}

void CodeWriter::Visit(ast::Gt* node) {
  VisitGroupedList('>', node->operands);
}

void CodeWriter::Visit(ast::SetVar* node) {
  fw.Write(node->name);
  fw.Write('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::SetAttr* node) {
  fw.Write(node->obj_name);
  fw.Write('.');
  fw.Write(node->attr->name);
  fw.Write('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::DefVar* node) {
  write_type(&module, node->type, &fw);

  fw.Write(' ');
  fw.Write(node->name);
  fw.Write('=');
  node->value->Accept(this);
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
  fw.Write(node->func->name);
  fw.Write('(');
  VisitList(',', node->args);
  fw.Write(')');
}

void CodeWriter::Visit(ast::CompoundLiteral* node) {
  sym::Struct* s = module.Struct(node->type.Tag());

  fw.Write("(struct ", 8);
  fw.Write(s->name);
  fw.Write("){", 2);
  VisitList(',', node->initializers);
  fw.Write('}');
}

void CodeWriter::Visit(ast::AttrAccess* node) {
  fw.Write(node->obj_name);
  fw.Write('.');
  fw.Write(node->attr->name);
}

void CodeWriter::VisitButLast(char delimiter, const NodeList& nodes) {
  if (nodes.size()) {
    for (uint i = 0; i < nodes.size() - 1; ++i) {
      nodes[i]->Accept(this);
      fw.Write(delimiter);
    }
  }
}

void CodeWriter::VisitList(char delimiter, const NodeList& nodes) {
  if (nodes.size()) {
    VisitButLast(delimiter, nodes);
    nodes.back()->Accept(this);
  }
}

void CodeWriter::VisitGroupedList(char delimiter, const NodeList& list) {
  fw.Write('(');
  VisitList(delimiter, list);
  fw.Write(')');
}

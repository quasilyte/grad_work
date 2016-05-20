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
#include "backend/cpp/cg/file_writer.hpp"
#include "intrinsic/intrinsic.hpp"

using namespace cpp_cg;
using namespace sym;

void CodeWriter::Run(ast::Node* node, const sym::Module& module, const cpp_cg::FileWriter& fw) {
  CodeWriter self{module, fw};
  self.Visit(node);
}

CodeWriter::CodeWriter(const sym::Module& module, const cpp_cg::FileWriter& fw):
module{module}, fw{fw} {}

void CodeWriter::Visit(ast::Node* node) {
  node->Accept(this);
}

void CodeWriter::Visit(ast::Int* node) {
  fw.module.Write(node->datum);
}

void CodeWriter::Visit(ast::Real* node) {
  fw.module.Write(node->datum);
}

void CodeWriter::Visit(ast::Str* node) {
  fw.module.Write(node->datum);
}

void CodeWriter::Visit(ast::Sym*) {
  fw.module.Write("SYM", 3);
}

void CodeWriter::Visit(ast::Sum* node) {
  VisitGroupedList('+', node->operands);
}

void CodeWriter::Visit(ast::Sub* node) {
  VisitGroupedList('-', node->operands);
}

void CodeWriter::Visit(ast::Mul* node) {
  VisitGroupedList('*', node->operands);
}

void CodeWriter::Visit(ast::Lt* node) {
  VisitGroupedList('<', node->operands);
}

void CodeWriter::Visit(ast::Gt* node) {
  VisitGroupedList('>', node->operands);
}

void CodeWriter::Visit(ast::SetVar* node) {
  fw.module.Write(node->name);
  fw.module.Write('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::SetAttr* node) {
  fw.module.Write(node->obj_name);
  fw.module.Write('.');
  fw.module.Write(node->attr->name);
  fw.module.Write('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::DefVar* node) {
  if (node->type.IsFunc()) {
    if (node->type.IsIntrinsic()) {
      auto ty = node->type;
      auto ret_ty = intrinsic::ret_type_of(ty);
      auto arity = intrinsic::arity_of(ty);

      write_type(&module, ret_ty, &fw.module);
      fw.module.Write("(*", 2);
      fw.module.Write(node->name);
      fw.module.Write(')');

      if (arity) {
        fw.module.Write('(');
        for (uint i = 0; i < arity - 1; ++i) {
          write_type(&module, intrinsic::param_of(ty, i), &fw.module);
          fw.module.Write(',');
        }
        write_type(&module, intrinsic::param_of(ty, arity - 1), &fw.module);
        fw.module.Write(')');
      } else {
        fw.module.Write("()");
      }
    } else {
      throw "DefVar: no assignments for user defined funcs yet";
    }
  } else {
    write_type(&module, node->type, &fw.module);
    fw.module.Write(' ');
    fw.module.Write(node->name);
  }

  fw.module.Write('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::If* node) {
  fw.module.Write("(");
  node->cond->Accept(this);
  fw.module.Write(")?(");
  node->on_true->Accept(this);
  fw.module.Write("):(");
  node->on_false->Accept(this);
  fw.module.Write(")");
}

void CodeWriter::Visit(ast::Var* node) {
  fw.module.Write(node->name);
}

void CodeWriter::Visit(ast::FuncCall* node) {
  write_func_name(node->func, &fw.module);
  fw.module.Write('(');
  VisitList(',', node->args);
  fw.module.Write(')');
}

void CodeWriter::Visit(ast::CompoundLiteral* node) {
  sym::Struct* s = module.Struct(node->type.Tag());

  fw.module.Write("(struct ", 8);
  fw.module.Write(s->name);
  fw.module.Write("){", 2);
  VisitList(',', node->initializers);
  fw.module.Write('}');
}

void CodeWriter::Visit(ast::AttrAccess* node) {
  fw.module.Write(node->obj_name);
  fw.module.Write('.');
  fw.module.Write(node->attr->name);
}

void CodeWriter::Visit(ast::Intrinsic* node) {
  fw.module.Write(intrinsic_name(node->type));
}

void CodeWriter::Visit(ast::IntrinsicCall1* node) {
  fw.module.Write(intrinsic_name(node->type));
  fw.module.Write('(');
  node->arg->Accept(this);
  fw.module.Write(')');
}

void CodeWriter::VisitButLast(char delimiter, const NodeList& nodes) {
  if (nodes.size()) {
    for (uint i = 0; i < nodes.size() - 1; ++i) {
      nodes[i]->Accept(this);
      fw.module.Write(delimiter);
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
  fw.module.Write('(');
  VisitList(delimiter, list);
  fw.module.Write(')');
}

void CodeWriter::Call(dt::StrView name, ast::Node *arg) {
  fw.module.Write(name);
  fw.module.Write('(');
  arg->Accept(this);
  fw.module.Write(')');
}

void CodeWriter::Cast(ast::Node* expr, Type target_ty) {
  fw.module.Write("((", 2);
  fw.module.Write(type_name(target_ty));
  fw.module.Write(')');
  expr->Accept(this);
  fw.module.Write(')');
}

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
#include "intrinsic/type_ops.hpp"
#include "cc/translation_unit.hpp"
#include "di/output.hpp"

using namespace cpp_cg;
using namespace sym;
using namespace dt;
using namespace di;

void CodeWriter::Run(ast::Node* node, const cc::TranslationUnit& tu) {
  CodeWriter self{tu};
  self.Visit(node);
}

CodeWriter::CodeWriter(const cc::TranslationUnit& tu): tu{tu} {}

void CodeWriter::Visit(ast::Node* node) {
  node->Accept(this);
}

void CodeWriter::Visit(ast::Int* node) {
  module_write(node->datum);
}

void CodeWriter::Visit(ast::Real* node) {
  module_write(node->datum);
}

void CodeWriter::Visit(ast::Str* node) {
  module_write(node->datum);
}

void CodeWriter::Visit(ast::Sym*) {
  module_write("SYM", 3);
}

void CodeWriter::Visit(ast::Sum* node) {
  // No need for unary "+" because it is mostly NOOP
  VisitGroupedList('+', node->operands);
}

void CodeWriter::Visit(ast::Sub* node) {
  if (1 == node->operands.size()) {
    VisitUnary('-', node->operands[0]);
  } else {
    VisitGroupedList('-', node->operands);
  }
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
  module_write(node->name);
  module_write('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::SetAttr* node) {
  module_write(node->obj_name);
  module_write('.');
  module_write(node->attr->name);
  module_write('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::DefVar* node) {
  if (node->type.IsFunc()) {
    if (node->type.IsIntrinsic()) {
      auto ty = node->type;
      auto ret_ty = intrinsic::ret_type_of(ty);
      auto arity = intrinsic::arity_of(ty);

      write_type(&tu.module, ret_ty);
      module_write("(*", 2);
      module_write(node->name);
      module_write(')');

      if (arity) {
        module_write('(');
        for (uint i = 0; i < arity - 1; ++i) {
          write_type(&tu.module, intrinsic::param_of(ty, i));
          module_write(',');
        }
        write_type(&tu.module, intrinsic::param_of(ty, arity - 1));
        module_write(')');
      } else {
        module_write("()", 2);
      }
    } else {
      uint arity;
      Type ret_ty;
      std::vector<sym::Param> params;

      if (node->type.IsLambda()) {
        sym::Lambda* lambda = tu.lambdas[Type::LambdaKey(node->type.Tag())];
        arity = lambda->Arity();
        ret_ty = lambda->ret_type;
        params = lambda->params;
      } else {
        auto func = tu.module.Func(node->type.Tag());
        arity = func->Arity();
        ret_ty = func->ret_type;
        params = func->params;
      }

      write_type(&tu.module, ret_ty);
      module_write("(*", 2);
      module_write(node->name);
      module_write(')');

      if (arity) {
        module_write('(');
        for (uint i = 0; i < arity - 1; ++i) {
          write_type(&tu.module, params[i].type);
          module_write(',');
        }
        write_type(&tu.module, params.back().type);
        module_write(')');
      } else {
        module_write("()", 2);
      }
    }
  } else {
    write_type(&tu.module, node->type);
    module_write(' ');
    module_write(node->name);
  }

  module_write('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::If* node) {
  module_write("(");
  node->cond->Accept(this);
  module_write(")?(");
  node->on_true->Accept(this);
  module_write("):(");
  node->on_false->Accept(this);
  module_write(")");
}

void CodeWriter::Visit(ast::Var* node) {
  module_write(node->name);
}

void CodeWriter::Visit(ast::LambdaExpr* node) {
  auto lambda = tu.lambdas[Type::LambdaKey(node->id)];
  write_lambda_name(lambda);
}

void CodeWriter::Visit(ast::FuncCall* node) {
  write_func_name(node->func);
  VisitGroupedList(',', node->args);
}

void CodeWriter::Visit(ast::VarCall* node) {
  module_write(node->name);
  VisitGroupedList(',', node->args);
}

void CodeWriter::Visit(ast::CompoundLiteral* node) {
  sym::Struct* s = tu.module.Struct(node->type.Tag());

  module_write("(struct ", 8);
  module_write(s->name);
  module_write("){", 2);
  VisitList(',', node->initializers);
  module_write('}');
}

void CodeWriter::Visit(ast::AttrAccess* node) {
  module_write(node->obj_name);
  module_write('.');
  module_write(node->attr->name);
}

void CodeWriter::Visit(ast::Intrinsic* node) {
  module_write(intrinsic_name(node->type));
}

void CodeWriter::Visit(ast::IntrinsicCall1* node) {
  module_write(intrinsic_name(node->type));
  module_write('(');
  node->arg->Accept(this);
  module_write(')');
}

void CodeWriter::VisitButLast(char delimiter, const NodeList& nodes) {
  if (nodes.size()) {
    for (uint i = 0; i < nodes.size() - 1; ++i) {
      nodes[i]->Accept(this);
      module_write(delimiter);
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
  module_write('(');
  VisitList(delimiter, list);
  module_write(')');
}

void CodeWriter::Call(dt::StrView name, ast::Node *arg) {
  module_write(name);
  module_write('(');
  arg->Accept(this);
  module_write(')');
}

void CodeWriter::Cast(ast::Node* expr, Type target_ty) {
  module_write("((", 2);
  module_write(type_name(target_ty));
  module_write(')');
  expr->Accept(this);
  module_write(')');
}

void CodeWriter::VisitUnary(char op, ast::Node* node) {
  module_write('(');
  module_write(op);
  node->Accept(this);
  module_write(')');
}

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
#include "io/file_writer.hpp"

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
  module_writer()(node->datum);
}

void CodeWriter::Visit(ast::Real* node) {
  module_writer()(node->datum);
}

void CodeWriter::Visit(ast::Str* node) {
  module_writer()(node->datum);
}

void CodeWriter::Visit(ast::Sym*) {
  module_writer()("SYM", 3);
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
  module_writer()(node->name);
  module_writer()('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::SetAttr* node) {
  module_writer()(node->obj_name);
  module_writer()('.');
  module_writer()(node->attr->name);
  module_writer()('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::DefVar* node) {
  if (node->type.IsFunc()) {
    if (node->type.IsIntrinsic()) {
      auto ty = node->type;
      auto ret_ty = intrinsic::ret_type_of(ty);
      auto arity = intrinsic::arity_of(ty);

      write_type(&tu.module, ret_ty);
      module_writer()("(*", 2)(node->name)(')');

      if (arity) {
        module_writer()('(');
        for (uint i = 0; i < arity - 1; ++i) {
          write_type(&tu.module, intrinsic::param_of(ty, i));
          module_writer()(',');
        }
        write_type(&tu.module, intrinsic::param_of(ty, arity - 1));
        module_writer()(')');
      } else {
        module_writer()("()", 2);
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
      module_writer()("(*", 2)(node->name)(')');

      if (arity) {
        module_writer()('(');
        for (uint i = 0; i < arity - 1; ++i) {
          write_type(&tu.module, params[i].type);
          module_writer()(',');
        }
        write_type(&tu.module, params.back().type);
        module_writer()(')');
      } else {
        module_writer()("()", 2);
      }
    }
  } else {
    write_type(&tu.module, node->type);
    module_writer()(' ')(node->name);
  }

  module_writer()('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::If* node) {
  module_writer()("(");
  node->cond->Accept(this);
  module_writer()(")?(");
  node->on_true->Accept(this);
  module_writer()("):(");
  node->on_false->Accept(this);
  module_writer()(")");
}

void CodeWriter::Visit(ast::Var* node) {
  module_writer()(node->name);
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
  module_writer()(node->name);
  VisitGroupedList(',', node->args);
}

void CodeWriter::Visit(ast::CompoundLiteral* node) {
  sym::Struct* s = tu.module.Struct(node->type.Tag());

  module_writer()("(struct ", 8)(s->name)("){", 2);
  VisitList(',', node->initializers);
  module_writer()('}');
}

void CodeWriter::Visit(ast::AttrAccess* node) {
  module_writer()(node->obj_name)('.')(node->attr->name);
}

void CodeWriter::Visit(ast::Intrinsic* node) {
  module_writer()(intrinsic_name(node->type));
}

void CodeWriter::Visit(ast::IntrinsicCall1* node) {
  module_writer()(intrinsic_name(node->type))('(');
  node->arg->Accept(this);
  module_writer()(')');
}

void CodeWriter::VisitButLast(char delimiter, const NodeList& nodes) {
  if (nodes.size()) {
    for (uint i = 0; i < nodes.size() - 1; ++i) {
      nodes[i]->Accept(this);
      module_writer()(delimiter);
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
  module_writer()('(');
  VisitList(delimiter, list);
  module_writer()(')');
}

void CodeWriter::Call(dt::StrView name, ast::Node *arg) {
  module_writer()(name)('(');
  arg->Accept(this);
  module_writer()(')');
}

void CodeWriter::Cast(ast::Node* expr, Type target_ty) {
  module_writer()("((", 2)(type_name(target_ty))(')');
  expr->Accept(this);
  module_writer()(')');
}

void CodeWriter::VisitUnary(char op, ast::Node* node) {
  module_writer()('(')(op);
  node->Accept(this);
  module_writer()(')');
}

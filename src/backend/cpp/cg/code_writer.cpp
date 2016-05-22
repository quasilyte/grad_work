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

void write_ptr(Lambda* lambda, const cc::TranslationUnit& tu) {
  while (lambda->ret_type.IsFunc()) {
    module_writer()("(*");
    lambda = lambda->ret_type.IsLambda()
        ? tu.lambdas[Type::LambdaKey(lambda->ret_type.Tag())]
        : tu.module.Func(lambda->ret_type.Tag());
  }
}

void write_ptr_params(Lambda* lambda, const cc::TranslationUnit& tu) {
  while (lambda->ret_type.IsFunc()) {
    write_params(tu, lambda->Params());
    module_writer()(')');

    lambda = lambda->ret_type.IsLambda()
        ? tu.lambdas[Type::LambdaKey(lambda->ret_type.Tag())]
        : tu.module.Func(lambda->ret_type.Tag());

  }
}

const std::vector<Param>& deep_params(Lambda* lambda, const cc::TranslationUnit& tu) {
  while (lambda->ret_type.IsFunc()) {
    lambda = lambda->ret_type.IsLambda()
        ? tu.lambdas[Type::LambdaKey(lambda->ret_type.Tag())]
        : tu.module.Func(lambda->ret_type.Tag());
  }

  return lambda->Params();
}

void CodeWriter::Run(ast::Node* node, const cc::TranslationUnit& tu) {
  CodeWriter self{tu};
  self.Visit(node);
}

void CodeWriter::RunButLast(char delimiter, const NodeList& nodes, const cc::TranslationUnit& tu) {
  CodeWriter self{tu};

  if (nodes.size()) {
    for (uint i = 0; i < nodes.size() - 1; ++i) {
      nodes[i]->Accept(&self);
      module_writer()(delimiter);
    }
  }
}

void CodeWriter::RunList(char delimiter, const NodeList& nodes, const cc::TranslationUnit& tu) {
  CodeWriter self{tu};

  if (nodes.size()) {
    RunButLast(delimiter, nodes, tu);
    nodes.back()->Accept(&self);
  }
}

void CodeWriter::RunGroupedList(char delimiter, const NodeList& list, const cc::TranslationUnit& tu) {
  module_writer()('(');
  RunList(delimiter, list, tu);
  module_writer()(')');
}

void CodeWriter::RunReturn(ast::Node* node, const cc::TranslationUnit& tu) {
  module_writer()("return ");
  Run(node, tu);
  module_writer()(';');
}

void CodeWriter::RunLambda(Lambda* l, const cc::TranslationUnit& tu) {
  if (l->ret_type.IsFunc()) {
    Lambda* lambda = l->ret_type.IsLambda()
        ? tu.lambdas[Type::LambdaKey(l->ret_type.Tag())]
        : tu.module.Func(l->ret_type.Tag());

    write_type(tu, lambda->ret_type);
    write_ptr(lambda, tu);
    module_writer()("(*");
    write_lambda_name(l);
    write_named_params(tu, l->Params());
    module_writer()(')');
    write_ptr_params(lambda, tu);
    write_params(tu, deep_params(l, tu));
  } else {
    write_type(tu, l->ret_type);
    module_writer()(' ');
    write_lambda_name(l);
    write_named_params(tu, l->Params());
  }

  RunBlock(l->exprs, tu);
}

/*
int      x2       (int x) { return x + x; }
int(*get_x2(void))(int)   { return x2; }

    (*                        (void))
Int_  (*get_ten_getter0(void))       (void){return get_ten0;}
Int_(*(*get_ten_getter0(void))(void))(void){return get_ten0;}

*/

void CodeWriter::RunFunc(Func* f, const cc::TranslationUnit& tu) {
  if (f->ret_type.IsFunc()) {
    Lambda* lambda = f->ret_type.IsLambda()
        ? tu.lambdas[Type::LambdaKey(f->ret_type.Tag())]
        : tu.module.Func(f->ret_type.Tag());

    write_type(tu, lambda->ret_type);
    write_ptr(lambda, tu);
    module_writer()("(*");
    write_func_name(f);
    write_named_params(tu, f->Params());
    module_writer()(')');
    write_ptr_params(lambda, tu);
    write_params(tu, deep_params(f, tu));
  } else {
    write_type(tu, f->ret_type);
    module_writer()(' ');
    write_func_name(f);
    write_named_params(tu, f->Params());
  }

  RunBlock(f->exprs, tu);
}

void CodeWriter::RunBlock(const NodeList& exprs, const cc::TranslationUnit& tu) {
  module_writer()('{');
  CodeWriter::RunButLast(';', exprs, tu);
  CodeWriter::RunReturn(exprs.back(), tu);
  module_writer()('}');
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
  RunGroupedList('+', node->operands, tu);
}

void CodeWriter::Visit(ast::Sub* node) {
  if (1 == node->operands.size()) {
    VisitUnary('-', node->operands[0]);
  } else {
    RunGroupedList('-', node->operands, tu);
  }
}

void CodeWriter::Visit(ast::Mul* node) {
  RunGroupedList('*', node->operands, tu);
}

void CodeWriter::Visit(ast::Lt* node) {
  RunGroupedList('<', node->operands, tu);
}

void CodeWriter::Visit(ast::Gt* node) {
  RunGroupedList('>', node->operands, tu);
}

void CodeWriter::Visit(ast::SetVar* node) {
  module_writer()(node->name)('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::SetAttr* node) {
  module_writer()(node->obj_name)('.')(node->attr->name)('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::DefVar* node) {
  if (node->type.IsFunc()) {
    if (node->type.IsIntrinsic()) {
      auto ty = node->type;

      module_writer()(type_name(intrinsic::ret_type_of(ty)))("(*")(node->name)(')');
      write_intrinsic_params(ty);
    } else {
      sym::Lambda* lambda = node->type.IsLambda()
          ? tu.lambdas[Type::LambdaKey(node->type.Tag())]
          : tu.module.Func(node->type.Tag());

      write_type(tu, lambda->ret_type);
      module_writer()("(*")(node->name)(')');
      write_params(tu, lambda->params);
    }
  } else {
    write_type(tu, node->type);
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
  write_lambda_name(tu.lambdas[Type::LambdaKey(node->id)]);
}

void CodeWriter::Visit(ast::FuncCall* node) {
  write_func_name(node->func);
  RunGroupedList(',', node->args, tu);
}

void CodeWriter::Visit(ast::VarCall* node) {
  module_writer()(node->name);
  RunGroupedList(',', node->args, tu);
}

void CodeWriter::Visit(ast::CompoundLiteral* node) {
  sym::Struct* s = tu.module.Struct(node->type.Tag());

  module_writer()("(struct ")(s->name)("){");
  RunList(',', node->initializers, tu);
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

void CodeWriter::Call(dt::StrView name, ast::Node *arg) {
  module_writer()(name)('(');
  arg->Accept(this);
  module_writer()(')');
}

void CodeWriter::Cast(ast::Node* expr, Type target_ty) {
  module_writer()("((")(type_name(target_ty))(')');
  expr->Accept(this);
  module_writer()(')');
}

void CodeWriter::VisitUnary(char op, ast::Node* node) {
  module_writer()('(')(op);
  node->Accept(this);
  module_writer()(')');
}

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
#include "unit/fns.hpp"
#include "unit/structs.hpp"

using namespace cpp_cg;
using namespace sym;
using namespace dt;
using namespace di;

void write_ptr(Fn* lambda) {
  while (lambda->ret_type.IsFn()) {
    module_writer()("(*");
    lambda = unit::get_fn(lambda->ret_type);
  }
}

void write_ptr_params(Fn* lambda, const cc::TranslationUnit& tu) {
  while (lambda->ret_type.IsFn()) {
    write_params(tu, lambda->Params());
    module_writer()(')');

    lambda = unit::get_fn(lambda->ret_type);
  }
}

const std::vector<Param>& deep_params(Fn* lambda) {
  while (lambda->ret_type.IsFn()) {
    lambda = unit::get_fn(lambda->ret_type);
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

void CodeWriter::RunLambda(UnnamedFn* l, const cc::TranslationUnit& tu) {
  if (l->ret_type.IsFn()) {
    Fn* lambda = unit::get_fn(l->ret_type);

    write_type(tu, lambda->ret_type);
    write_ptr(lambda);
    module_writer()("(*");
    write_lambda_name(l);
    write_named_params(tu, l->Params());
    module_writer()(')');
    write_ptr_params(lambda, tu);
    write_params(tu, deep_params(l));
  } else {
    write_type(tu, l->ret_type);
    module_writer()(' ');
    write_lambda_name(l);
    write_named_params(tu, l->Params());
  }

  RunBlock(l->exprs, tu);
}

void CodeWriter::RunFunc(NamedFn* f, const cc::TranslationUnit& tu) {
  if (f->ret_type.IsFn()) {
    Fn* lambda = unit::get_fn(f->ret_type);

    write_type(tu, lambda->ret_type);
    write_ptr(lambda);
    module_writer()("(*");
    write_func_name(f);
    write_named_params(tu, f->Params());
    module_writer()(')');
    write_ptr_params(lambda, tu);
    write_params(tu, deep_params(f));
  } else if (f->ret_type.IsDynDispatcher()) {
    MultiFn* multi_fn = unit::get_multi_fn(f->ret_type);

    module_writer()("Any(*");
    write_func_name(f);
    write_named_params(tu, f->Params());
    module_writer()(')');

    switch (multi_fn->arity) {
    case 1: module_writer()("(Any)"); break;
    case 2: module_writer()("(Any,Any)"); break;
    case 3: module_writer()("(Any,Any,Any)"); break;
    default: throw "dyn dispatcher arity overflow";
    }
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
  if (node->type.IsFn()) {
    if (node->type.IsIntrinsic()) {
      auto ty = node->type;

      module_writer()(type_name(intrinsic::ret_type_of(ty)))("(*")(node->name)(')');
      write_intrinsic_params(ty);
    } else {
      sym::Fn* lambda = unit::get_fn(node->type);

      write_type(tu, lambda->ret_type);
      module_writer()("(*")(node->name)(')');
      write_params(tu, lambda->params);
    }
  } else if (node->type.IsDynDispatcher()) {
    MultiFn* multi_fn = unit::get_multi_fn(node->type);
    module_writer()("Any(*")(node->name)(")(");
    for (uint i = 0; i < multi_fn->arity - 1; ++i) {
      module_writer()("Any,");
    }
    module_writer()("Any)");
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
  write_lambda_name(unit::get_fn(node->type.Id()));
}

void CodeWriter::Visit(ast::FuncCall* node) {
  write_func_name(node->func);
  RunGroupedList(',', node->args, tu);
}

void CodeWriter::Visit(ast::VarCall* node) {
  module_writer()(node->name);
  RunGroupedList(',', node->args, tu);
}

void CodeWriter::Visit(ast::DynamicCall* node) {
  module_writer()(node->func->name);
  RunGroupedList(',', node->args, tu);
}

void CodeWriter::Visit(ast::CompoundLiteral* node) {
  sym::Struct* st = unit::get_struct(node->type);

  module_writer()("(struct ")(st->name)("){");
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

void CodeWriter::Visit(ast::Each* node) {
  module_writer()("for(");
  write_type(tu, node->next_fn->ret_type);
  module_writer()(" _=");
  node->init->Accept(this);
  module_writer()(';');

  write_func_name(node->has_next_fn);
  module_writer()("(_);_=");
  write_func_name(node->next_fn);
  module_writer()("(_)){");
  write_type(tu, node->current_fn->ret_type);
  module_writer()(' ')(node->iter_name)('=');
  write_func_name(node->current_fn);
  module_writer()("(_);");
  node->body->Accept(this);
  module_writer()(";}");
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

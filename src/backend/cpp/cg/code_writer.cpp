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
#include "io/file_writer.hpp"
#include "unit/fns.hpp"
#include "unit/structs.hpp"
#include "backend/cpp/cg/state.hpp"
#include "sym/sym.hpp"
#include "di/pipe.hpp"

using namespace cpp_cg;
using namespace sym;
using namespace dt;
using namespace di;

void write_ptr(Fn* lambda) {
  while (lambda->ret_type.IsFn()) {
    get_pipe()("(*");
    lambda = unit::get_fn(lambda->ret_type);
  }
}

void write_ptr_params(Fn* lambda, const cc::TranslationUnit& tu) {
  while (lambda->ret_type.IsFn()) {
    write_params(tu, lambda->Params());
    get_pipe()(')');

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
      get_pipe()(delimiter);
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
  get_pipe()('(');
  RunList(delimiter, list, tu);
  get_pipe()(')');
}

void CodeWriter::RunReturn(ast::Node* node, const cc::TranslationUnit& tu) {
  get_pipe()("return ");
  Run(node, tu);
  get_pipe()(';');
}

void CodeWriter::RunLambda(UnnamedFn* l, const cc::TranslationUnit& tu) {
  if (l->ret_type.IsFn()) {
    Fn* lambda = unit::get_fn(l->ret_type);

    write_type(tu, lambda->ret_type);
    write_ptr(lambda);
    get_pipe()("(*");
    write_lambda_name(l);
    write_named_params(tu, l->Params());
    get_pipe()(')');
    write_ptr_params(lambda, tu);
    write_params(tu, deep_params(l));
  } else {
    write_type(tu, l->ret_type);
    get_pipe()(' ');
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
    get_pipe()("(*");
    write_func_name(f);
    write_named_params(tu, f->Params());
    get_pipe()(')');
    write_ptr_params(lambda, tu);
    write_params(tu, deep_params(f));
  } else if (f->ret_type.IsDynDispatcher()) {
    MultiFn* multi_fn = unit::get_multi_fn(f->ret_type);

    get_pipe()("Any(*");
    write_func_name(f);
    write_named_params(tu, f->Params());
    get_pipe()(')');

    switch (multi_fn->arity) {
    case 1: get_pipe()("(Any)"); break;
    case 2: get_pipe()("(Any,Any)"); break;
    case 3: get_pipe()("(Any,Any,Any)"); break;
    default: throw "dyn dispatcher arity overflow";
    }
  } else {
    write_type(tu, f->ret_type);
    get_pipe()(' ');
    write_func_name(f);
    write_named_params(tu, f->Params());
  }

  RunBlock(f->exprs, tu);
}

void CodeWriter::RunBlock(const NodeList& exprs, const cc::TranslationUnit& tu) {
  get_pipe()('{');
  CodeWriter::RunButLast(';', exprs, tu);
  CodeWriter::RunReturn(exprs.back(), tu);
  get_pipe()('}');
}

CodeWriter::CodeWriter(const cc::TranslationUnit& tu): tu{tu} {}

void CodeWriter::Visit(ast::Node* node) {
  node->Accept(this);
}

void CodeWriter::Visit(ast::Int* node) {
  get_pipe()(node->datum);
}

void CodeWriter::Visit(ast::Real* node) {
  get_pipe()(node->datum);
}

void CodeWriter::Visit(ast::Str* node) {
  get_pipe()(node->datum);
}

void CodeWriter::Visit(ast::Sym*) {
  get_pipe()("SYM", 3);
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
  get_pipe()(node->name)('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::SetAttr* node) {
  get_pipe()(node->obj_name)('.')(node->attr->name)('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::DefVar* node) {
  if (node->type.IsFn()) {
    if (node->type.IsIntrinsic()) {
      auto ty = node->type;

      get_pipe()(type_name(intrinsic::ret_type_of(ty)))("(*")(node->name)(')');
      write_intrinsic_params(ty);
    } else {
      sym::Fn* lambda = unit::get_fn(node->type);

      write_type(tu, lambda->ret_type);
      get_pipe()("(*")(node->name)(')');
      write_params(tu, lambda->params);
    }
  } else if (node->type.IsDynDispatcher()) {
    MultiFn* multi_fn = unit::get_multi_fn(node->type);
    get_pipe()("Any(*")(node->name)(")(");
    for (uint i = 0; i < multi_fn->arity - 1; ++i) {
      get_pipe()("Any,");
    }
    get_pipe()("Any)");
  } else {
    write_type(tu, node->type);
    get_pipe()(' ')(node->name);
  }

  get_pipe()('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::If* node) {
  get_pipe()("(");
  node->cond->Accept(this);
  get_pipe()(")?(");
  node->on_true->Accept(this);
  get_pipe()("):(");
  node->on_false->Accept(this);
  get_pipe()(")");
}

void CodeWriter::Visit(ast::IntCase* node) {
  set_pipe(runtime_fw);

  auto suffix = gen_suffix(switch_count);

  get_pipe()(type_name(node->ret_type))(" switch")(suffix);
  get_pipe()("(Int x){switch(x){");
  for (const ast::IntCase::Clause& clause : node->clauses) {
    get_pipe()("case ")(clause.cond)(":return ");
    clause.expr->Accept(this);
    get_pipe()(';');
  }
  get_pipe()("}}");

  switch_count += 1;
  set_pipe(module_fw);

  get_pipe()("switch")(suffix)('(');
  node->cond_expr->Accept(this);
  get_pipe()(')');
}

void CodeWriter::Visit(ast::Var* node) {
  get_pipe()(node->name);
}

void CodeWriter::Visit(ast::LambdaExpr* node) {
  write_lambda_name(unit::get_fn(node->type.Id()));
}

void CodeWriter::Visit(ast::FuncCall* node) {
  write_func_name(node->func);
  RunGroupedList(',', node->args, tu);
}

void CodeWriter::Visit(ast::VarCall* node) {
  get_pipe()(node->name);
  RunGroupedList(',', node->args, tu);
}

void CodeWriter::Visit(ast::DynamicCall* node) {
  get_pipe()(node->func->name);
  RunGroupedList(',', node->args, tu);
}

void CodeWriter::Visit(ast::CompoundLiteral* node) {
  sym::Struct* st = unit::get_struct(node->type);

  get_pipe()("(struct ")(st->name)("){");
  RunList(',', node->initializers, tu);
  get_pipe()('}');
}

void CodeWriter::Visit(ast::AttrAccess* node) {
  get_pipe()(node->obj_name)('.')(node->attr->name);
}

void CodeWriter::Visit(ast::Intrinsic* node) {
  get_pipe()(intrinsic_name(node->type));
}

void CodeWriter::Visit(ast::IntrinsicCall1* node) {
  get_pipe()(intrinsic_name(node->type))('(');
  node->arg->Accept(this);
  get_pipe()(')');
}

void CodeWriter::Visit(ast::Each* node) {
  get_pipe()("for(");
  write_type(tu, node->next_fn->ret_type);
  get_pipe()(" _=");
  node->init->Accept(this);
  get_pipe()(';');

  write_func_name(node->has_next_fn);
  get_pipe()("(_);_=");
  write_func_name(node->next_fn);
  get_pipe()("(_)){");
  write_type(tu, node->current_fn->ret_type);
  get_pipe()(' ')(node->iter_name)('=');
  write_func_name(node->current_fn);
  get_pipe()("(_);");
  node->body->Accept(this);
  get_pipe()(";}");
}

void CodeWriter::Call(dt::StrView name, ast::Node *arg) {
  get_pipe()(name)('(');
  arg->Accept(this);
  get_pipe()(')');
}

void CodeWriter::Cast(ast::Node* expr, Type target_ty) {
  get_pipe()("((")(type_name(target_ty))(')');
  expr->Accept(this);
  get_pipe()(')');
}

void CodeWriter::VisitUnary(char op, ast::Node* node) {
  get_pipe()('(')(op);
  node->Accept(this);
  get_pipe()(')');
}

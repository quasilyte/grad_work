#include "backend/c/cg/code_writer.hpp"

#include "ast/node.hpp"
#include "ast/defs.hpp"
#include "ast/builtins.hpp"
#include "ast/binary_ops.hpp"
#include "ast/statements.hpp"
#include "ast/literals.hpp"
#include "ast/cond.hpp"
#include "sym/module.hpp"
#include "sym/struct.hpp"
#include "backend/c/cg/type_map.hpp"
#include "backend/c/cg/utils.hpp"
#include "intrinsic/type_ops.hpp"
#include "io/file_writer.hpp"
#include "unit/fns.hpp"
#include "unit/structs.hpp"
#include "backend/c/cg/state.hpp"
#include "sym/sym.hpp"
#include "di/pipe.hpp"

using namespace c_cg;
using namespace sym;
using namespace dt;
using namespace di;

void write_ptr(Fn* lambda) {
  while (lambda->ret_type.IsFn()) {
    get_pipe()("(*");
    lambda = unit::get_fn(lambda->ret_type);
  }
}

void write_ptr_params(Fn* lambda) {
  while (lambda->ret_type.IsFn()) {
    write_params(lambda->Params());
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

void CodeWriter::Run(ast::Node* node) {
  CodeWriter self;
  self.Visit(node);
}

void CodeWriter::RunButLast(char delimiter, const NodeList& nodes) {
  CodeWriter self;

  if (nodes.size()) {
    for (uint i = 0; i < nodes.size() - 1; ++i) {
      nodes[i]->Accept(&self);
      get_pipe()(delimiter);
    }
  }
}

void CodeWriter::RunList(char delimiter, const NodeList& nodes) {
  CodeWriter self;

  if (nodes.size()) {
    RunButLast(delimiter, nodes);
    nodes.back()->Accept(&self);
  }
}

void CodeWriter::RunGroupedList(char delimiter, const NodeList& list) {
  get_pipe()('(');
  RunList(delimiter, list);
  get_pipe()(')');
}

void CodeWriter::RunLambda(UnnamedFn* l) {
  if (l->ret_type.IsFn()) {
    Fn* lambda = unit::get_fn(l->ret_type);

    write_type(lambda->ret_type);
    write_ptr(lambda);
    get_pipe()("(*");
    write_lambda_name(l);
    write_named_params(l->Params());
    get_pipe()(')');
    write_ptr_params(lambda);
    write_params(deep_params(l));
  } else {
    write_type(l->ret_type);
    get_pipe()(' ');
    write_lambda_name(l);
    write_named_params(l->Params());
  }

  RunBlock(l->exprs);
}

void CodeWriter::RunMonoFn(MonoFn* fn) {
  write_type(fn->ret_type);
  get_pipe()(' ');
  get_pipe()(fn->name);
  write_named_params(fn->Params());

  RunBlock(fn->exprs);
}

void CodeWriter::RunFunc(NamedFn* f) {
  if (f->ret_type.IsFn()) {
    Fn* lambda = unit::get_fn(f->ret_type);

    write_type(lambda->ret_type);
    write_ptr(lambda);
    get_pipe()("(*");
    write_func_name(f);
    write_named_params(f->Params());
    get_pipe()(')');
    write_ptr_params(lambda);
    write_params(deep_params(f));
  } else if (f->ret_type.IsDynDispatcher()) {
    MultiFn* multi_fn = unit::get_multi_fn(f->ret_type);

    get_pipe()("Any(*");
    write_func_name(f);
    write_named_params(f->Params());
    get_pipe()(')');

    switch (multi_fn->arity) {
    case 1: get_pipe()("(Any)"); break;
    case 2: get_pipe()("(Any,Any)"); break;
    case 3: get_pipe()("(Any,Any,Any)"); break;
    default: throw "dyn dispatcher arity overflow";
    }
  } else {
    write_type(f->ret_type);
    get_pipe()(' ');
    write_func_name(f);
    write_named_params(f->Params());
  }

  RunBlock(f->exprs);
}

void CodeWriter::RunBlock(const NodeList& exprs) {
  get_pipe()('{');
  CodeWriter::RunList(';', exprs);
  get_pipe()('}');
}

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

void CodeWriter::Visit(ast::Sum* node) {
  VisitBinary('+', node->operands);
}

void CodeWriter::Visit(ast::SumAssign* node) {
  // x += expr
  get_pipe()(node->target)("+=");
  node->val->Accept(this);
}

void CodeWriter::Visit(ast::Sub* node) {
  VisitBinary('-', node->operands);
}

void CodeWriter::Visit(ast::Mul* node) {
  VisitBinary('*', node->operands);
}

void CodeWriter::Visit(ast::Div* node) {
  VisitBinary('/', node->operands);
}

void CodeWriter::Visit(ast::NumLt* node) {
  VisitBinary('<', node->operands);
}

void CodeWriter::Visit(ast::NumGt* node) {
  VisitBinary('>', node->operands);
}

void CodeWriter::Visit(ast::NumEq* node) {
  VisitBinary("==", node->operands);
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

      write_type(lambda->ret_type);
      get_pipe()("(*")(node->name)(')');
      write_params(lambda->params);
    }
  } else if (node->type.IsDynDispatcher()) {
    MultiFn* multi_fn = unit::get_multi_fn(node->type);
    get_pipe()("Any(*")(node->name)(")(");
    for (uint i = 0; i < multi_fn->arity - 1; ++i) {
      get_pipe()("Any,");
    }
    get_pipe()("Any)");
  } else {
    write_type(node->type);
    get_pipe()(' ')(node->name);
  }

  get_pipe()('=');
  node->value->Accept(this);
}

void CodeWriter::Visit(ast::IfExpr* node) {
  get_pipe()("(");
  node->cond->Accept(this);
  get_pipe()(")?(");
  node->on_true->Accept(this);
  get_pipe()("):(");
  node->on_false->Accept(this);
  get_pipe()(")");
}

void CodeWriter::Visit(ast::IfStmt* node) {
  get_pipe()("if(");
  node->cond->Accept(this);
  get_pipe()("){");
  RunList(';', node->on_true);
  get_pipe()('}');

  if (node->on_false.size()) {
    get_pipe()("else{");
    RunList(';', node->on_false);
    get_pipe()('}');
  }
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
  RunGroupedList(',', node->args);
}

void CodeWriter::Visit(ast::MonoFnCall* node) {
  get_pipe()(node->fn->name);
  RunGroupedList(',', node->args);
}

void CodeWriter::Visit(ast::VarCall* node) {
  get_pipe()(node->name);
  RunGroupedList(',', node->args);
}

void CodeWriter::Visit(ast::DynamicCall* node) {
  get_pipe()(node->func->name);
  RunGroupedList(',', node->args);
}

void CodeWriter::Visit(ast::CompoundLit* node) {
  sym::Struct* st = unit::get_struct(node->type);

  get_pipe()("(struct ")(st->name)("){");
  RunList(',', node->initializers);
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
  write_type(node->next_fn->ret_type);
  get_pipe()(" _=");
  node->init->Accept(this);
  get_pipe()(';');

  write_func_name(node->has_next_fn);
  get_pipe()("(_);_=");
  write_func_name(node->next_fn);
  get_pipe()("(_)){");
  write_type(node->current_fn->ret_type);
  get_pipe()(' ')(node->iter_name)('=');
  write_func_name(node->current_fn);
  get_pipe()("(_);");
  node->body->Accept(this);
  get_pipe()(";}");
}

void CodeWriter::Visit(ast::Return* node) {
  get_pipe()("return ");
  node->val->Accept(this);
  get_pipe()(';');
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

template<class T>
void CodeWriter::VisitBinary(T op, const ast::BinaryNode& node) {
  get_pipe()('(');
  node.lhs->Accept(this);
  get_pipe()(op);
  node.rhs->Accept(this);
  get_pipe()(')');
}

template void CodeWriter::VisitBinary(char, const ast::BinaryNode&);
template void CodeWriter::VisitBinary(const char*, const ast::BinaryNode&);

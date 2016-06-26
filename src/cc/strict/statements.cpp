#include <cc/strict/statements.hpp>

#include <ast/cond.hpp>
#include <ast/statements.hpp>
#include <unit/scope.hpp>
#include <err/type_errors.hpp>
#include <err/sym_errors.hpp>

using namespace cc;
using namespace ast;

Node* cc::strict_assign(dt::StrView recv_name, Node* expr) {
  auto recv_type = unit::scope_symbol(recv_name);
  if (recv_type.IsVoid()) {
    throw err::UndefinedSymbol{recv_name};
  }

  if (recv_type.SameAs(expr->Type())) {
    return new ast::Assign{recv_name, expr};
  } else {
    throw err::VarTypeMismatch{recv_type, expr->Type(), recv_name};
  }
}

Node* cc::strict_sum_assign(dt::StrView recv_name, Node* expr) {
  auto recv_type = unit::scope_symbol(recv_name);

  if (!recv_type.IsArith()) {
    throw err::InvalidTypeInArith{recv_type, "+="};
  }

  if (recv_type.SameAs(expr->Type())) {
    return new SumAssign{recv_name, expr};
  } else {
    throw err::MixedArithTypes{recv_type, expr->Type(), "+="};
  }
}

Node* cc::strict_if_stmt(Node* cond, NodeList&& on_true, NodeList&& on_false) {
  auto cond_type = cond->Type();

  if (cond_type.IsBool()) {
    return new ast::IfStmt{cond, std::move(on_true), std::move(on_false)};
  } else {
    throw err::NonBoolCondition{cond_type};
  }
}

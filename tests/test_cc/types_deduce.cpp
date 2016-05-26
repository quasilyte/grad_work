#include "test_cc/suit.hpp"

#include "unit/structs.hpp"
#include "unit/fns.hpp"
#include "cc/type_deducer.hpp"
#include "ast/atoms.hpp"
#include "test_utils.hpp"
#include "dt/str_view.hpp"

using cc::TypeDeducer;
using sym::Type;

void test_prim_types_deduce() {
  TRUE(TypeDeducer::Run(new ast::Int{"10"}).IsInt());
  TRUE(TypeDeducer::Run(new ast::Real{"1.0"}).IsReal());
}

void test_struct_types_deduce() {
  sym::Struct* point_st = unit::get_struct("Point");
  auto expr1 = new ast::CompoundLiteral{
    {new ast::Int{"1"}, new ast::Int{"2"}},
    point_st->type,
  };
  auto type1 = TypeDeducer::Run(expr1);
  TRUE(type1.IsStruct());
  TRUE(type1.Id() == point_st->type.Id());

  sym::Struct* num_st = unit::get_struct("Num");
  auto expr2 = new ast::CompoundLiteral{
    {new ast::Real{"1"}},
    num_st->type,
  };
  auto type2 = TypeDeducer::Run(expr2);
  TRUE(type2.IsStruct());
  TRUE(type2.Id() == num_st->type.Id());
}

void test_unnamed_fn_types_deduce() {
  sym::Type unnamed_fn1 = unit::new_unnamed_fn(
    {{"a", Type::Int()}},
    {new ast::Int("1")},
    Type::Int()
  );
  TRUE(unnamed_fn1.IsUnnamedFn());
  TRUE(0 == unnamed_fn1.Id());

  sym::Type unnamed_fn2 = unit::new_unnamed_fn(
    {{"a", Type::Real()}},
    {new ast::Real("1.0")},
    Type::Real()
  );
  TRUE(unnamed_fn2.IsUnnamedFn());
  TRUE(1 == unnamed_fn2.Id());
}

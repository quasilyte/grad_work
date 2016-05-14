#include "test_sym/suit.hpp"

#include "test_utils.hpp"
#include "sym/scope.hpp"

using namespace sym;
using namespace dt;

void test_scope() {
  Scope scope;

  scope.CreateLevel();
  scope.DropLevel();

  auto ty1 = Type::Int();
  auto ty2 = Type::Real();
  StrView key1{"x"};
  StrView key2{"veryLongIdentifier"};

  scope.CreateLevel();
  scope.DefineSymbol(key1, &ty1);
  scope.DefineSymbol(key2, &ty2);
  TRUE(scope.Symbol(key1)->IsInt());
  TRUE(scope.Symbol(key2)->IsReal());

  scope.CreateLevel();
  scope.DefineSymbol(key1, &ty2);
  TRUE(scope.Symbol(key1)->IsReal());
  TRUE(scope.Symbol(key2)->IsReal());
  TRUE(scope.LocalSymbol(key2) == nullptr);

  scope.DropLevel();
  TRUE(scope.Symbol(key1)->IsInt());
  TRUE(scope.Symbol(key2)->IsReal());
  FALSE(scope.LocalSymbol(key2) == nullptr);
}

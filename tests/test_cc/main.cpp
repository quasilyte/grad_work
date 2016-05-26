#include "suit.hpp"

#include "unit/structs.hpp"
#include "sym/type.hpp"
#include "test_utils.hpp"

using sym::Type;

void init() {
  unit::def_struct("Point", {
    {"x", Type::Int()},
    {"y", Type::Int()},
  });

  unit::def_struct("Num", {
    {"val", Type::Real()},
  });
}

int main() {
  init();

  RUN(prim_types_deduce);
  RUN(struct_types_deduce);
  RUN(unnamed_fn_types_deduce);

  FINISH();
}

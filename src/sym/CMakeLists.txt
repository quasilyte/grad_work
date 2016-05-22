project(sym)

set(
  sym_src
  sym.cpp
  type.cpp
  module.cpp
  generator.cpp
  scope.cpp
  struct.cpp
  fn.cpp
  rules.cpp
)

add_library(sym STATIC ${sym_src})

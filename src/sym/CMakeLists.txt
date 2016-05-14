project(sym)

set(
  sym_src
  sym.cpp
  type.cpp
  func.cpp
  module.cpp
  generator.cpp
  scope.cpp
)

add_library(sym STATIC ${sym_src})

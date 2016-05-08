project(sym)

set(
  sym_src
  sym.cpp
  type.cpp
  signature.cpp
  module.cpp
)

add_library(sym STATIC ${sym_src})

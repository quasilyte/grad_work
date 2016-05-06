project(sym)

set(
  sym_src
  table.cpp
  type.cpp
  signature.cpp
)

add_library(sym STATIC ${sym_src})

project(sym)

set(
  sym_src
  table.cpp
  type.cpp
  signature.cpp
  modules.cpp
)

add_library(sym STATIC ${sym_src})

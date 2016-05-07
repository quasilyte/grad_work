project(ast)

set(
  ast_src

  node.cpp
  cond.cpp
  atoms.cpp
  defs.cpp
)

add_library(ast STATIC ${ast_src})

project(ast)

set(
  ast_src
  cond.cpp
  literals.cpp
  defs.cpp
  builtins.cpp
  binary_ops.cpp
  node.cpp
  statements.cpp
)

add_library(ast STATIC ${ast_src})

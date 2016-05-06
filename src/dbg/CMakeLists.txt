project(dbg)

set(
  dbg_src
  lex.cpp
)

add_library(dbg STATIC ${dbg_src})

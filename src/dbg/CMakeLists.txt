project(dbg)

set(
  dbg_src
  lex.cpp
  dt.cpp
)

add_library(dbg STATIC ${dbg_src})

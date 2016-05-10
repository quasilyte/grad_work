project(cpp_cg)

set(
  cpp_cg_src
  code_gen.cpp
)

add_library(cpp_cg STATIC ${cpp_cg_src})

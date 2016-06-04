project(cpp_cg)

set(
  cpp_cg_src
  type_map.cpp
  code_writer.cpp
  translator.cpp
  utils.cpp
  state.cpp
)

add_library(cpp_cg STATIC ${cpp_cg_src})

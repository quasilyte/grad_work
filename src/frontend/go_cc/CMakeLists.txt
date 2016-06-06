project(go_cc)

set(
  go_cc_src
  classifier.cpp
  parser.cpp
  char_groups.cpp
  reader.cpp
  types.cpp
  expr_parsing.cpp
  stmt_parsing.cpp
  parsing.cpp
  fn_parsing.cpp
  cursor_ext.cpp
  type_parsing.cpp
)

add_library(go_cc STATIC ${go_cc_src})

project(cc)

set(
  cc_src
  strict/arith.cpp
  strict/type_check.cpp
  strict/statements.cpp
  fn_check.cpp
  parse_lit.cpp
)

add_library(cc STATIC ${cc_src})

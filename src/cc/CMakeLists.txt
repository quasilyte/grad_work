project(cc)

set(
  cc_src
  strict_arith.cpp
  fn_check.cpp
  parse_lit.cpp
)

add_library(cc STATIC ${cc_src})

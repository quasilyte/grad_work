project(err)

set(
  err_src
  abstract_error.cpp
  sym_errors.cpp
  type_errors.cpp
  lex_errors.cpp
  fn_errors.cpp
)

add_library(err STATIC ${err_src})

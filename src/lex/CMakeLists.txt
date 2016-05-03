project(lex)

set(
  lex_src
  char_type.cpp
  token.cpp
  token_stream.cpp
  parse_val.cpp
)

add_library(lex STATIC ${lex_src})

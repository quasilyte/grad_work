project(lex)

set(
  lex_src
  token_stream.cpp
  char_type.cpp
  token.cpp
)

add_library(lex STATIC ${lex_src})

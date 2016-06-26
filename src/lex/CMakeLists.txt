project(lex)

set(
  lex_src
  char_type.cpp
  reader.cpp
  num_tagger.cpp
  c/comment.cpp
)

add_library(lex STATIC ${lex_src})

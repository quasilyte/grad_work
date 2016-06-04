project(lex)

set(
  lex_src
  char_type.cpp
  # reader.cpp
  char_groups.cpp
  num_tagger.cpp
  gen_alphabet.cpp
  cursor.cpp
)

add_library(lex STATIC ${lex_src})

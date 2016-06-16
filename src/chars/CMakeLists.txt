project(chars)

set(
  chars_src
  categories.cpp
  alphabet.cpp
)

add_library(chars STATIC ${chars_src})

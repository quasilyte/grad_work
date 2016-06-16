project(rodata)

set(
  rodata_src
  cstrings.cpp
)

add_library(rodata STATIC ${rodata_src})

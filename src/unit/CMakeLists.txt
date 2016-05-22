project(unit)

set(
  unit_src
  fns.cpp
  syms.cpp
  structs.cpp
)

add_library(unit STATIC ${unit_src})

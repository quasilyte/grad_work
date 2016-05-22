project(unit)

set(
  unit_src
  fns.cpp
  syms.cpp
)

add_library(unit STATIC ${unit_src})

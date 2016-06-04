project(unit)

set(
  unit_src
  fns.cpp
  structs.cpp
  globals.cpp
  scope.cpp
  source.cpp
)

add_library(unit STATIC ${unit_src})

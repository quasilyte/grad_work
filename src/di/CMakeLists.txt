project(di)

set(
  di_src
  output.cpp
  unit.cpp
)

add_library(di STATIC ${di_src})

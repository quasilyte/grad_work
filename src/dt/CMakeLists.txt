project(dt)

set(
  dt_src
  str_view.cpp
  dict.cpp
)

add_library(dt STATIC ${dt_src})

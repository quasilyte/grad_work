project(dt)

set(
  dt_src
  str_view.cpp
  dict.cpp
  hlist.cpp
  alist.cpp
)

add_library(dt STATIC ${dt_src})

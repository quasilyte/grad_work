project(fmt)

set(
  fmt_src
  u64.cpp
)

add_library(fmt STATIC ${fmt_src})

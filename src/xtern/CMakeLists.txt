project(xtern)

set(
  xtern_src
  pkg_encoder.cpp
  pkg_type_encoder.cpp
  pkg_fn_encoder.cpp
)

add_library(xtern STATIC ${xtern_src})

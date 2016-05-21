project(intrinsic)

set(
  intrinsic_src
  type_ops.cpp
  overloadings.cpp
)

add_library(intrinsic STATIC ${intrinsic_src})

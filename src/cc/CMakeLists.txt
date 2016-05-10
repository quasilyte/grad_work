project(cc)

set(
  cc_src
  classifier.cpp
  parser.cpp
  code_gen.cpp
)

add_library(cc STATIC ${cc_src})

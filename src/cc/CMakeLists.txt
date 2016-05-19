project(cc)

set(
  cc_src
  type_deducer.cpp
  classifier.cpp
  parser.cpp
)

add_library(cc STATIC ${cc_src})

project(test_cc)

set(
  test_cc_src
  main.cpp
  types_deduce.cpp
)

add_executable(test_cc ${test_cc_src})
target_link_libraries(test_cc ast unit dt cc sym intrinsic)

add_test(test_cc test_cc)

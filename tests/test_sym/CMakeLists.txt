project(sym_test)

set(
  sym_test_src
  scope.cpp
  main.cpp
)

add_executable(sym_test ${sym_test_src})
target_link_libraries(sym_test sym dt)

add_test(sym_test sym_test)

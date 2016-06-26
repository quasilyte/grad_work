project(lex_test)

set(
  lex_test_src
  simple_tests.cpp
  main.cpp
)

add_executable(lex_test ${lex_test_src})
target_link_libraries(lex_test lex chars dt rodata dbg err unit)

add_test(lex_test lex_test)

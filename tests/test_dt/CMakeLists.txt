project(dt_test)

set(
  dt_test_src
  alist.cpp
  main.cpp
)

add_executable(dt_test ${dt_test_src})
target_link_libraries(dt_test dt)

add_test(dt_test dt_test)

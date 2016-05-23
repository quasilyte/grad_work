project(app)

set(
  app_src
  app.cpp
  api.cpp
)

add_library(app STATIC ${app_src})

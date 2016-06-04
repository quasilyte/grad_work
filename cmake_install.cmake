# Install script for directory: /home/quasilyte/CODE/GIT/dipl/Resembler

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/lex/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/dbg/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/cc/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/ast/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/io/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/sym/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/intrinsic/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/dt/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/fmt/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/backend/c/cg/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/frontend/go_cc/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/di/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/util/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/unit/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/src/app/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/tests/test_dt/cmake_install.cmake")
  include("/home/quasilyte/CODE/GIT/dipl/Resembler/tests/test_cc/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "/home/quasilyte/CODE/GIT/dipl/Resembler/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "/home/quasilyte/CODE/GIT/dipl/Resembler/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()

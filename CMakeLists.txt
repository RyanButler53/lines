cmake_minimum_required(VERSION 3.15...3.26)

project(lines LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#pip install --no-build-isolarion -ve
add_subdirectory(src)

option(WITH_PYTHON_BINDINGS OFF "With Python Bindings")
if (WITH_PYTHON_BINDINGS)
  message(STATUS "Building Python Bindings")
  add_subdirectory(python_bindings)
else()
  message (STATUS "Building Unit Tests")
  enable_testing()
  add_subdirectory(tests)
endif()
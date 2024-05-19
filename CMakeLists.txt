cmake_minimum_required(VERSION 3.14)
project(lines)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  lines_test
  lines_test.cpp
)

add_executable(
    toplines
    toplines.cpp
    # lines.cpp
)

# set_property(TARGET lines_test VS_DEBUGGER_WORKING_DIRECTORY "/usr/local/bin/gdb")

target_link_libraries(
  lines_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lines_test)
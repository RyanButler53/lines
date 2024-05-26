cmake_minimum_required(VERSION 3.14)
project(lines)

# cmake --build build --target clean
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# set(GCC_UBSAN_COMPILE_FLAGS "-fsanitize=undefined -fsanitize=address")
# set(GCC_UBSAN_LINK_FLAGS    "-fsanitize=undefined -fsanitize=address")

set(CMAKE_CXX_FLAGS "${GCC_UBSAN_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${GCC_UBSAN_LINK_FLAGS}")

# Tests
add_executable(
  lines_test
  src/lines_test.cpp
  src/lines.cpp
  src/fraction.cpp
)
add_executable(
    fraction_test
    src/fraction_test.cpp
    src/fraction.cpp
)

# Production
add_executable(
    toplines
    src/toplines.cpp
    src/lines.cpp
    src/fraction.cpp
)

add_executable(
    trails
    src/trails.cpp
    src/lines.cpp
    src/fraction.cpp
)

target_link_libraries(
  lines_test
  GTest::gtest_main
)

target_link_libraries(
  fraction_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lines_test)
gtest_discover_tests(fraction_test)
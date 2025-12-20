cmake_minimum_required(VERSION 4.0)
project(lines)


# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(GCC_UBSAN_COMPILE_FLAGS "-fsanitize=undefined -fsanitize=address")
# set(GCC_UBSAN_LINK_FLAGS    "-fsanitize=undefined -fsanitize=address")

set(CMAKE_CXX_FLAGS "${GCC_UBSAN_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${GCC_UBSAN_LINK_FLAGS}")

include_directories(inc) # not great but works
add_subdirectory(src)
add_subdirectory(tests)
set(LINES_SRC fraction.cpp lines.cpp)

add_library(lines ${LINES_SRC})
target_include_directories(lines PUBLIC inc)

# toplines and trails fns will be namespaced in lines library
add_executable(toplines toplines.cpp)
add_executable(trails trails.cpp)

target_link_libraries(toplines PUBLIC lines)
target_link_libraries(trails PUBLIC lines)

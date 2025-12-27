add_library(lines lines.cpp fraction.cpp)
target_include_directories(lines PUBLIC ${PROJECT_SOURCE_DIR}/inc)
set_target_properties(lines PROPERTIES POSITION_INDEPENDENT_CODE ON)

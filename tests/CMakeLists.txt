include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
macro ( addLinesTest testname src)
    add_executable("${testname}_test" ${src})
    gtest_add_tests(TARGET "${testname}_test" SOURCES ${src} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries("${testname}_test" lines GTest::gtest_main)
    

  endmacro()

addLinesTest(fraction fraction_test.cpp)
addLinesTest(lines lines_test.cpp)

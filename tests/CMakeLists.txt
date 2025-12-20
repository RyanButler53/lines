include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 
)
FetchContent_MakeAvailable(googletest)

enable_testing()

macro ( addLinesTest testname src)
    add_executable("${testname}_test" ${src})
    target_link_libraries("${testname}_test" lines GTest::gtest_main)
endmacro()

addLinesTest(fraction fraction_test.cpp)
addLinesTest(lines lines_test.cpp)

include(GoogleTest)
gtest_discover_tests(lines_test)
gtest_discover_tests(fraction_test)
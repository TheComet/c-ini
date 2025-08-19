enable_testing ()

project ("c-ini-tests"
    LANGUAGES C CXX)

# GoogleTest requires at least C++17
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include (FetchContent)
FetchContent_Declare (
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.x)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

c_ini_generate (
    INPUT "test_parse_types.cpp"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/test_parse_types.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/test_parse_types.c")
c_ini_generate (
    INPUT "test_fixed_str.cpp"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/test_fixed_str.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/test_fixed_str.c")
c_ini_generate (
    INPUT "test_dynamic_str.cpp"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/test_dynamic_str.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/test_dynamic_str.c")
c_ini_generate (
    INPUT "test_custom_str.cpp"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/test_custom_str.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/test_custom_str.c"
    INCLUDE_DIRS "${PROJECT_SOURCE_DIR}")
c_ini_generate (
    INPUT "test_fixed_strlist.cpp"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/test_fixed_strlist.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/test_fixed_strlist.c")
c_ini_generate (
    INPUT "test_dynamic_strlist.cpp"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/test_dynamic_strlist.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/test_dynamic_strlist.c")

add_executable (c_ini_tests
    "test_parse_types.cpp"
    "${PROJECT_BINARY_DIR}/test_parse_types.h"
    "${PROJECT_BINARY_DIR}/test_parse_types.c"
    "test_fixed_str.cpp"
    "${PROJECT_BINARY_DIR}/test_fixed_str.h"
    "${PROJECT_BINARY_DIR}/test_fixed_str.c"
    "test_dynamic_str.cpp"
    "${PROJECT_BINARY_DIR}/test_dynamic_str.h"
    "${PROJECT_BINARY_DIR}/test_dynamic_str.c"
    "test_custom_str.cpp"
    "custom_str.cpp"
    "${PROJECT_BINARY_DIR}/test_custom_str.h"
    "${PROJECT_BINARY_DIR}/test_custom_str.c"
    "test_fixed_strlist.cpp"
    "${PROJECT_BINARY_DIR}/test_fixed_strlist.h"
    "${PROJECT_BINARY_DIR}/test_fixed_strlist.c"
    "test_dynamic_strlist.cpp"
    "${PROJECT_BINARY_DIR}/test_dynamic_strlist.h"
    "${PROJECT_BINARY_DIR}/test_dynamic_strlist.c")
target_include_directories (c_ini_tests PRIVATE
    "${PROJECT_BINARY_DIR}")
target_link_libraries (c_ini_tests PRIVATE
    c_ini
    GTest::gmock
    GTest::gmock_main)

project ("c-ini-examples"
    LANGUAGES C)

# Example 1
c_ini_generate (
    INPUT "example1.c"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/example1/include/example1/settings_ini.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/example1/src/settings_ini.c")
add_executable (c_ini_example1
    "example1.c"
    "${PROJECT_BINARY_DIR}/example1/include/example1/settings_ini.h"
    "${PROJECT_BINARY_DIR}/example1/src/settings_ini.c")
target_include_directories (c_ini_example1 PRIVATE
    "${PROJECT_BINARY_DIR}/example1/include")
target_compile_options (c_ini_example1 PRIVATE
    $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -ansi>)
target_link_libraries (c_ini_example1 PRIVATE c_ini)

# Example 2
c_ini_generate (
    INPUT "example2_client.h" "example2_server.h"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/example2/include/example2/settings_ini.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/example2/src/settings_ini.c")
add_executable (c_ini_example2
    "example2.c"
    "${PROJECT_BINARY_DIR}/example2/include/example2/settings_ini.h"
    "${PROJECT_BINARY_DIR}/example2/src/settings_ini.c")
target_include_directories (c_ini_example2 PRIVATE
    "${PROJECT_BINARY_DIR}/example2/include")
target_compile_options (c_ini_example2 PRIVATE
    $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -ansi>)
target_link_libraries (c_ini_example2 PRIVATE c_ini)

# Example 3
c_ini_generate (
    INPUT "example3.c"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/example3/include/example3/player_ini.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/example3/src/player_ini.c")
add_executable (c_ini_example3
    "example3.c"
    "${PROJECT_BINARY_DIR}/example3/include/example3/player_ini.h"
    "${PROJECT_BINARY_DIR}/example3/src/player_ini.c")
target_include_directories (c_ini_example3 PRIVATE
    "${PROJECT_BINARY_DIR}/example3/include")
target_compile_options (c_ini_example3 PRIVATE
    $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -ansi>)
target_link_libraries (c_ini_example3 PRIVATE c_ini)
set_target_properties (c_ini_example3 PROPERTIES
    C_STANDARD 99)


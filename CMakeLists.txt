cmake_minimum_required (VERSION 3.21)

project ("c-ini"
    VERSION 1.0.0
    LANGUAGES C)

option (C_INI_EXAMPLES "Build examples" OFF)

add_executable (c_ini_generator "c-ini/c-ini.c")
target_compile_options (c_ini_generator PRIVATE
    $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -ansi>)
set_target_properties (c_ini_generator PROPERTIES
    C_STANDARD 90
    C_EXTENSIONS NO)

function (c_ini_generate)
    cmake_parse_arguments (ARG "" "HEADER;SOURCE" "INPUT" ${ARGN})
    if (NOT ARG_HEADER)
        message (FATAL_ERROR "HEADER argument is required")
    endif ()
    if (NOT ARG_SOURCE)
        message (FATAL_ERROR "SOURCE argument is required")
    endif ()

    get_filename_component (ARG_HEADER_DIR ${ARG_HEADER} DIRECTORY)
    get_filename_component (ARG_SOURCE_DIR ${ARG_SOURCE} DIRECTORY)
    
    add_custom_command (OUTPUT ${ARG_HEADER} ${ARG_SOURCE}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ARG_HEADER_DIR} ${ARG_SOURCE_DIR}
        COMMAND c_ini_generator
        ARGS --header ${ARG_HEADER} --source ${ARG_SOURCE} --input ${ARG_INPUT}
        DEPENDS c_ini_generator
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "--header ${ARG_HEADER} --source ${ARG_SOURCE} --input ${ARG_INPUT}"
        VERBATIM)
endfunction ()

add_library (c_ini INTERFACE "c-ini/c-ini.h")
target_include_directories (c_ini INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/c-ini>"
    $<INSTALL_INTERFACE:include>)

if (C_INI_EXAMPLES)
    c_ini_generate (
        INPUT "${PROJECT_SOURCE_DIR}/examples/example1.c"
        HEADER "${PROJECT_BINARY_DIR}/example1/include/example1/settings_ini.h"
        SOURCE "${PROJECT_BINARY_DIR}/example1/src/settings_ini.c")
    add_executable (c_ini_example1
        "examples/example1.c"
        "${PROJECT_BINARY_DIR}/example1/include/example1/settings_ini.h"
        "${PROJECT_BINARY_DIR}/example1/src/settings_ini.c")
    target_include_directories (c_ini_example1 PRIVATE
        "${PROJECT_BINARY_DIR}/example1/include")
    target_compile_options (c_ini_example1 PRIVATE
        $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -ansi>)
    target_link_libraries (c_ini_example1 PRIVATE c_ini)

    c_ini_generate (
        INPUT
            "${PROJECT_SOURCE_DIR}/examples/example2_client.h"
            "${PROJECT_SOURCE_DIR}/examples/example2_server.h"
        HEADER "${PROJECT_BINARY_DIR}/example2/include/example2/settings_ini.h"
        SOURCE "${PROJECT_BINARY_DIR}/example2/src/settings_ini.c")
    add_executable (c_ini_example2
        "examples/example2.c"
        "${PROJECT_BINARY_DIR}/example2/include/example2/settings_ini.h"
        "${PROJECT_BINARY_DIR}/example2/src/settings_ini.c")
    target_include_directories (c_ini_example2 PRIVATE
        "${PROJECT_BINARY_DIR}/example2/include")
    target_compile_options (c_ini_example2 PRIVATE
        $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -ansi>)
    target_link_libraries (c_ini_example2 PRIVATE c_ini)

    c_ini_generate (
        INPUT "${PROJECT_SOURCE_DIR}/examples/example3.c"
        HEADER "${PROJECT_BINARY_DIR}/example3/include/example3/player_ini.h"
        SOURCE "${PROJECT_BINARY_DIR}/example3/src/player_ini.c")
    add_executable (c_ini_exmaple3
        "examples/example3.c"
        "${PROJECT_BINARY_DIR}/example3/include/example3/player_ini.h"
        "${PROJECT_BINARY_DIR}/example3/src/player_ini.c")
    target_include_directories (c_ini_exmaple3 PRIVATE
        "${PROJECT_BINARY_DIR}/example3/include")
    target_compile_options (c_ini_exmaple3 PRIVATE
        $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -ansi>)
    target_link_libraries (c_ini_exmaple3 PRIVATE c_ini)
endif ()

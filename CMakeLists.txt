cmake_minimum_required (VERSION 3.21)

project ("c-ini"
    VERSION 1.0.0
    LANGUAGES C)

option (C_INI_EXAMPLES "Build examples" OFF)
option (C_INI_TESTS "Build tests" OFF)

add_executable (c_ini_generator "c-ini/c-ini.c")
target_compile_options (c_ini_generator PRIVATE
    $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -ansi>)
set_target_properties (c_ini_generator PROPERTIES
    C_STANDARD 90
    C_EXTENSIONS NO)

add_library (c_ini INTERFACE "c-ini/c-ini.h")
target_include_directories (c_ini INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/c-ini>"
    $<INSTALL_INTERFACE:include>)

function (c_ini_generate)
    cmake_parse_arguments (ARG
        ""
        "OUTPUT_HEADER;OUTPUT_SOURCE"
        "INPUT"
        ${ARGN})
    if (NOT ARG_OUTPUT_HEADER)
        message (FATAL_ERROR "OUTPUT_HEADER argument is required")
    endif ()
    if (NOT ARG_OUTPUT_SOURCE)
        message (FATAL_ERROR "OUTPUT_SOURCE argument is required")
    endif ()

    get_filename_component (OUTPUT_HEADER_DIR ${ARG_OUTPUT_HEADER} DIRECTORY)
    get_filename_component (OUTPUT_SOURCE_DIR ${ARG_OUTPUT_SOURCE} DIRECTORY)

    set (ABSOLUTE_INPUT_FILES)
    foreach (INPUT_FILE IN LISTS ARG_INPUT)
        get_filename_component (ABSOLUTE_INPUT_FILE ${INPUT_FILE} ABSOLUTE)
        list (APPEND ABSOLUTE_INPUT_FILES ${ABSOLUTE_INPUT_FILE})
    endforeach ()
    
    add_custom_command (
        OUTPUT ${ARG_OUTPUT_HEADER} ${ARG_OUTPUT_SOURCE}
        COMMAND ${CMAKE_COMMAND}
            -E make_directory ${OUTPUT_HEADER_DIR} ${OUTPUT_SOURCE_DIR}
        COMMAND c_ini_generator
        ARGS --header ${ARG_OUTPUT_HEADER}
             --source ${ARG_OUTPUT_SOURCE}
             --input ${ABSOLUTE_INPUT_FILES}
        DEPENDS c_ini_generator ${ABSOLUTE_INPUT_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "--header ${ARG_OUTPUT_HEADER} --source ${ARG_OUTPUT_SOURCE} --input ${ABSOLUTE_INPUT_FILES}"
        VERBATIM)
endfunction ()

if (C_INI_EXAMPLES)
    add_subdirectory ("examples")
endif ()

if (C_INI_TESTS)
    add_subdirectory ("tests")
endif ()

cmake_minimum_required(VERSION 3.10)

project(
    utf-8-testing
    VERSION 0.0
    LANGUAGES CXX
)

add_executable(
    utf-8-test

    "main.cpp"

    "ConstChar.cpp"
    "StringTest.cpp"
    "FilePathTest.cpp"
    "FileReadTest.cpp"
    "FileWriteTest.cpp"

    "Log.h"
)

target_compile_features(
    utf-8-test
    PUBLIC
    cxx_std_20
)

if(MSVC)
    target_compile_options(
        utf-8-test
        PUBLIC
        /utf-8
    )
endif()

if(WIN32)
    target_compile_definitions(
        utf-8-test
        PUBLIC
        BUILD_WIN
    )
endif()

if(MSVC)
    add_custom_command(
        TARGET utf-8-test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/test-files
            ${CMAKE_BINARY_DIR}/$<CONFIG>/test-files
    )
else()
    add_custom_command(
        TARGET utf-8-test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/test-files
            ${CMAKE_BINARY_DIR}/test-files
)
endif()
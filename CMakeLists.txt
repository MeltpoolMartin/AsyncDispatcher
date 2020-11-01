cmake_minimum_required(VERSION 3.18.2)

project(
    AsyncDispatcher
    LANGUAGES CXX
)

#Workaround until gtest is available under clang 12
set(CONAN_DISABLE_CHECK_COMPILER TRUE)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
    message("conanbuildinfo_multi.cmake file found")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)

    CONAN_BASIC_SETUP(
        TARGETS
    )
elseif(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message("conanbuildinfo.cmake file found")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    CONAN_BASIC_SETUP(
        TARGETS
    )
else()
    message("No conanbuildinfo.cmake file found")
endif()

add_subdirectory(src)

option(CMake_RUN_CLANG_TIDY "Run clang-tidy with the compiler." OFF)
if(CMake_RUN_CLANG_TIDY)
    if(CMake_SOURCE_DIR STREQUAL CMake_BINARY_DIR)
        message(FATAL_ERROR "CMake_RUN_CLANG_TIDY requires an out-of-source build!")
    endif()
    find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
    if(NOT CLANG_TIDY_COMMAND)
        message(WARNING "CMake_RUN_CLANG_TIDY is ON but clang-tidy is not found!")
        set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE)
    else()
        message("clang-tidy enabled")
    endif()
endif()

option(UNIT_TESTS "Build unit tests" ON)
if(UNIT_TESTS)
    message("Build unit tests")
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()
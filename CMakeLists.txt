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

option(PACKAGE_TESTS "Build unit tests" ON)
if(PACKAGE_TESTS)
    message("Build unit tests")
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()
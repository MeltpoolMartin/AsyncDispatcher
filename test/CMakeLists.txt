cmake_minimum_required(VERSION 3.18.2)

project(testAsyncDispatcher LANGUAGES CXX)

add_executable(testAsyncDispatcher
    ${CMAKE_CURRENT_SOURCE_DIR}/testAsyncDispatcher.cpp
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test/${CMAKE_BUILD_TYPE}"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        AsyncDispatcherLib
        #CONAN_PKG::gtest
)

gtest_discover_tests(${PROJECT_NAME}
    WORKING_DIRECTORY
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# deploy_test_file(${PROJECT_NAME}
#     ${CMAKE_CURRENT_SOURCE_DIR}/data
#     $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
# )
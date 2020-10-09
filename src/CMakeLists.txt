cmake_minimum_required(VERSION 3.18.2)

project(AsyncDispatcherLib 
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} STATIC  
    ${CMAKE_SOURCE_DIR}/src/include/AsyncDispatcher/AsyncDispatcher.hpp
    ${CMAKE_SOURCE_DIR}/src/src/AsyncDispatcher.cpp
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib/${CMAKE_BUILD_TYPE}"
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib/${CMAKE_BUILD_TYPE}"
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include/AsyncDispatcher
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
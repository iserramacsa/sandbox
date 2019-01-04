cmake_minimum_required (VERSION 2.6)

set(PROJECT_NAME MClient)

project(${PROJECT_NAME})

set(SOURCES)
set(HEADERS)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(${PROJECT_SOURCE_DIR}/src $CMAKE_BINARY_DIR)
include_directories(${PROJECT_SOURCE_DIR}/src)


set(SOURCES ${SOURCES}
	main.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})

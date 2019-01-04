cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
set (CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")

set(PROJECT_NAME MClient)

project(${PROJECT_NAME})

set(SOURCES)
set(HEADERS)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)


include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/comms)
add_subdirectory(${PROJECT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src)


set(SOURCES ${SOURCES}
	mclient.cpp
	mprinter.cpp
	mprintermanager.cpp
	main.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})

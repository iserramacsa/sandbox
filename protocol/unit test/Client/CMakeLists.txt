cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
set (CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")

set(PROJECT_NAME MClient_UnitTest)
enable_testing()


set(SOURCES)
set(HEADERS)
set(INCLUDE_TESTS true)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include_directories(${PROJECT_SOURCE_DIR}/MCLient)
include_directories(${PROJECT_SOURCE_DIR}/MCLient/tests)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/comms)

add_subdirectory(${PROJECT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/MCLient/tests ${CMAKE_BINARY_DIR}/tests)


set(SOURCES ${SOURCES}
	${PROJECT_SOURCE_DIR}/MCLient/mclient.cpp
	${PROJECT_SOURCE_DIR}/MCLient/mprinter.cpp
	${PROJECT_SOURCE_DIR}/MCLient/mprintermanager.cpp
	main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
	/usr/lib/gtest/libgtest.a
	/usr/lib/libgmock.a
	-pthread
	)

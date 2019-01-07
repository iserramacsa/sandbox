cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
set (CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")

set(PROJECT_NAME MClient_UnitTest)
enable_testing()
add_definitions(-DMOCK_TEST)

set(SOURCES)
set(HEADERS)
set(INCLUDE_TESTS true)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/comms)
include_directories(${PROJECT_SOURCE_DIR}/src/client)

add_subdirectory(${PROJECT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/client ${CMAKE_BINARY_DIR}/client)


set(SOURCES ${SOURCES}
	main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
	/usr/lib/gtest/libgtest.a
	/usr/lib/libgmock.a
	-pthread
	)


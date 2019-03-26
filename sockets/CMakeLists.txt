cmake_minimum_required (VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)
set (CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")


############################
####     DEFINITIONS    ####
############################

set(PROJECT_NAME Sockets)
project(${PROJECT_NAME})

add_definitions(-DVIRTUAL_MOCK=)
add_definitions(-DDEBUG)

set(SOURCES)
set(HEADERS)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#########################
####     INCLUDES    ####
#########################
set(LOG TRUE)

set(INCLUDES)

#include_directories(${INCLUDES})
include_directories(${PROJECT_SOURCE_DIR}/src)

#############################
####     SOURCE FILES    ####
#############################
add_subdirectory(${PROJECT_SOURCE_DIR}/src			${CMAKE_BINARY_DIR}/src)

set(CLIENT  ${SOURCES}
	samples/client.cpp)

set(SERVER  ${SOURCES}
	samples/server.cpp)


set(CLIENT_LIB "${PROJECT_NAME}Client")
set(SERVER_LIB "${PROJECT_NAME}Server")


#######################
####     TARGET    ####
#######################

add_executable(${CLIENT_LIB} ${CLIENT})
add_executable(${SERVER_LIB} ${SERVER})

target_link_libraries(${CLIENT_LIB}
	pthread
	)
#target_link_libraries(${SERVER_LIB}
#	${EXTERNAL_LIBS}
#	)

cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)
set (CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")
#-Wall  -Wno-unused-parameter  -Wno-unused-but-set-variable  -Wno-unused-function
set (CMAKE_CXX_FLAGS ${CXX_FLAGS})
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g2 -Wno-unused-parameter")

add_definitions(-DDEBUG)

#PROJECT DEFINITION
set(PROJECT_NAME MUdpClient)
Project(${PROJECT_NAME})

## GLOBAL VARIABLES DEFINITION
set(SOURCES)
set(HEADERS)
set(EXTERNAL_LIBS pthread)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

##TODO -- Move these definitions to cmake_toolchain_file for arm compilations.
set(ARM 1)
if(ARM)
	set(CMAKE_PREFIX_PATH /opt/fsl-imx-x11/4.1.15-1.2.0/sysroots/cortexa7hf-vfp-neon-poky-linux-gnueabi)
endif()


## PROJECT SOURCES
set(SOURCES ${SOURCES}
	main.cpp
)
set(CLIENT TRUE)
set(SERVER TRUE)
add_subdirectory(${PROJECT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src)

##includes
##TODO -- Move these definitions to cmake_toolchain_file for arm compilations.
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/include
	${PROJECT_SOURCE_DIR}/src
	)

#EXECUTABLE AND LIBRARY LINKAGE
add_executable(${PROJECT_NAME} ${SOURCES})

if(EXTERNAL_LIBS)
	target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS})
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(PROTOCOL_VERSION_MAJOR 1)
set(PROTOCOL_VERSION_MINOR 0)
set(PROTOCOL_VERSION_PATCH 0)

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/version.h
  )


add_subdirectory(comms ${CMAKE_BINARY_DIR}/src/comms)

if (INCLUDE_TESTS)
	add_subdirectory(tests ${CMAKE_BINARY_DIR}/src/test)
endif()

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/commands.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2.cpp
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/iprotocol.h
	${CMAKE_CURRENT_SOURCE_DIR}/icommand.h
	${CMAKE_CURRENT_SOURCE_DIR}/commands.h

	PARENT_SCOPE
	)

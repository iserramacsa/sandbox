include_directories( ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

if (INCLUDE_TESTS)
	add_subdirectory(tests)
endif()


set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/mclient.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mprinter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mprintermanager.cpp
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)

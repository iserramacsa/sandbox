include_directories( ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()



set(SOURCES ${SOURCES}
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/isocket.h
	)

if (UNIX)
	set(SOURCES ${SOURCES}
		${CMAKE_CURRENT_SOURCE_DIR}/unixsocket.cpp
		)

	set(HEADERS ${HEADERS}
		${CMAKE_CURRENT_SOURCE_DIR}/unixsocket.h
		)
else()
	set(SOURCES ${SOURCES}
		${CMAKE_CURRENT_SOURCE_DIR}/winsockets.cpp
		)

	set(HEADERS ${HEADERS}
		${CMAKE_CURRENT_SOURCE_DIR}/winsockets.h
		)
endif()


set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)


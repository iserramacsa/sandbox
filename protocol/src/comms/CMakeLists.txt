include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (INCLUDE_TESTS)
	add_subdirectory(tests)
endif()

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/comms.cpp
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/comms.h
	)

if (UNIX)
set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/unixsockets.cpp
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/unixsockets.h
	PARENT_SCOPE
	)
else()
	set(SOURCES ${SOURCES}
		${CMAKE_CURRENT_SOURCE_DIR}/winsockets.cpp
		PARENT_SCOPE
		)

	set(HEADERS ${HEADERS}
		${CMAKE_CURRENT_SOURCE_DIR}/winsockets.h
		PARENT_SCOPE
		)
endif()



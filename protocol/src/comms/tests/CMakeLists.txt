include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/comms_UnitTest.cpp
	)

if (UNIX)
set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/unixsockets_UnitTest.cpp
	PARENT_SCOPE
	)
else()
	set(SOURCES ${SOURCES}
		${CMAKE_CURRENT_SOURCE_DIR}/winsockets_UnitTest.cpp
		PARENT_SCOPE
		)
endif()



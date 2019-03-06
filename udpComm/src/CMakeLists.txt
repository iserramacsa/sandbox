include_directories( ${CMAKE_CURRENT_SOURCE_DIR})

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(SRC)

set(SRC ${SRC}
	${CMAKE_CURRENT_SOURCE_DIR}/udpsocket.cpp
	)

if(SERVER)
	set(SRC ${SRC}
		${CMAKE_CURRENT_SOURCE_DIR}/udpserver.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/udpserverbcast.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/mserver.cpp
		)
endif()

if(CLIENT)
	set(SRC ${SRC}
		${CMAKE_CURRENT_SOURCE_DIR}/udpclient.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/udpclientbcast.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/mclient.cpp
		)
endif()


set(SOURCES ${SOURCES}
	${SRC}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)	

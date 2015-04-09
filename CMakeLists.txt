CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(LIBEMOJIDEX)

# Generate version header
SET(EMOJIDEX_LIB_VERSION_MAJOR 0)
SET(EMOJIDEX_LIB_VERSION_MINOR 1)
SET(EMOJIDEX_LIB_VERSION_PATCH 0)
SET(EMOJIDEX_LIB_VERSION "${EMOJIDEX_LIB_VERSION_MAJOR}.${EMOJIDEX_LIB_VERSION_MINOR}.${EMOJIDEX_LIB_VERSION_PATCH}")
CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/src/version.h.in ${PROJECT_SOURCE_DIR}/src/version.h @ONLY)

# SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

# We're using C++11
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

# rapidJSON is lib only so only uncomment this if you want to 
# also run specs on it
# ADD_SUBDIRECTORY(vendor/rapidjson)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/vendor/rapidjson/include
	)

ADD_LIBRARY(emojidex SHARED
	${PROJECT_SOURCE_DIR}/src/client.cpp
	${PROJECT_SOURCE_DIR}/src/service/transactor.cpp
	${PROJECT_SOURCE_DIR}/src/service/indexes.cpp
	${PROJECT_SOURCE_DIR}/src/service/search.cpp
	)

FIND_PACKAGE(Boost REQUIRED
	system
	filesystem
	)

FIND_PACKAGE(OpenSSL)


TARGET_LINK_LIBRARIES(emojidex
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${OPENSSL_LIBRARIES}
	)

ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/spec)

# Installation
INSTALL(FILES 
	${PROJECT_SOURCE_DIR}/src/version.h
	${PROJECT_SOURCE_DIR}/src/client.h
	${PROJECT_SOURCE_DIR}/src/service/indexes.h
	${PROJECT_SOURCE_DIR}/src/service/search.h
	${PROJECT_SOURCE_DIR}/src/data/moji_codes.h
	DESTINATION "include/emojidex"
	)
INSTALL(TARGETS emojidex DESTINATION "lib")

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(LIBEMOJIDEX)


# Generate version header
SET(EMOJIDEX_LIB_VERSION_MAJOR 0)
SET(EMOJIDEX_LIB_VERSION_MINOR 1)
SET(EMOJIDEX_LIB_VERSION_PATCH 0)
SET(EMOJIDEX_LIB_VERSION "${EMOJIDEX_LIB_VERSION_MAJOR}.${EMOJIDEX_LIB_VERSION_MINOR}.${EMOJIDEX_LIB_VERSION_PATCH}")
CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/src/version.h.in ${PROJECT_SOURCE_DIR}/src/version.h @ONLY)

# SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(BUILD_TESTS true)
SET(DO_DYNAMIC true)
SET(DO_INSTALL true)

# Options and interface builds
OPTION(ANDROID "Build native Android libs (for NDK) and libemojidex JAR.")
OPTION(JAVA "Build Java interfaces")
OPTION(RUBY "Build Ruby interfaces")
OPTION(OBJC "Build Objective-C interfaces")

# We're using C++11
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()
# TODO: can we use C++11 on windows? if so how to enable it here?

# Make this build an android build
IF(ANDROID)
	INCLUDE(${PROJECT_SOURCE_DIR}/interfaces/android/CMakeLists.txt)
ENDIF(ANDROID)

# rapidJSON is lib only so only uncomment this if you want to 
# also run specs on it
# ADD_SUBDIRECTORY(vendor/rapidjson)

SET(EMOJIDEX_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/vendor/rapidjson/include
)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${EMOJIDEX_INCLUDE_DIRS})

# Generate dynamic library
FIND_PACKAGE(Boost REQUIRED
	system
	filesystem
	date_time
	)
FIND_PACKAGE(OpenSSL)
FIND_PACKAGE(CURL)

SET(EMOJIDEX_DYNAMIC_LIB_TARGET emojidex)
SET(EMOJIDEX_CPP_FILES
	${PROJECT_SOURCE_DIR}/src/client.cpp
	${PROJECT_SOURCE_DIR}/src/service/settings.cpp
	${PROJECT_SOURCE_DIR}/src/service/transactor.cpp
	${PROJECT_SOURCE_DIR}/src/service/collector.cpp
	${PROJECT_SOURCE_DIR}/src/service/indexes.cpp
	${PROJECT_SOURCE_DIR}/src/service/search.cpp
	${PROJECT_SOURCE_DIR}/src/service/user.cpp
	${PROJECT_SOURCE_DIR}/src/service/user/history_item.cpp
	${PROJECT_SOURCE_DIR}/src/data/collection.cpp
	${PROJECT_SOURCE_DIR}/src/data/checksums.cpp
)

SET(EMOJIDEX_LINK_LIBRARIES
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${OPENSSL_LIBRARIES}
	${CURL_LIBRARIES}
)

IF(DO_DYNAMIC)
  ADD_LIBRARY(${EMOJIDEX_DYNAMIC_LIB_TARGET} SHARED ${EMOJIDEX_CPP_FILES})
  TARGET_LINK_LIBRARIES(${EMOJIDEX_DYNAMIC_LIB_TARGET} ${EMOJIDEX_LINK_LIBRARIES})
  SET_TARGET_PROPERTIES(${EMOJIDEX_DYNAMIC_LIB_TARGET}
    PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
  )
ENDIF(DO_DYNAMIC)

# Specs
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/spec)
ENABLE_TESTING()

# Installation
INSTALL(FILES 
	${PROJECT_SOURCE_DIR}/src/emojidex.h
	${PROJECT_SOURCE_DIR}/src/version.h
	${PROJECT_SOURCE_DIR}/src/client.h
	${PROJECT_SOURCE_DIR}/src/service/settings.h
	${PROJECT_SOURCE_DIR}/src/service/transactor.h
	${PROJECT_SOURCE_DIR}/src/service/collector.h
	${PROJECT_SOURCE_DIR}/src/service/indexes.h
	${PROJECT_SOURCE_DIR}/src/service/search.h
	${PROJECT_SOURCE_DIR}/src/service/user.h
	${PROJECT_SOURCE_DIR}/src/service/user/history_item.h
	${PROJECT_SOURCE_DIR}/src/data/emoji.h
	${PROJECT_SOURCE_DIR}/src/data/collection.h
	${PROJECT_SOURCE_DIR}/src/data/checksums.h
	${PROJECT_SOURCE_DIR}/src/data/moji_codes.h
	DESTINATION "include/emojidex"
	)
IF(DO_INSTALL)
  INSTALL(TARGETS ${EMOJIDEX_DYNAMIC_LIB_TARGET} DESTINATION "lib")
ENDIF(DO_INSTALL)


# Generate static library
SET(EMOJIDEX_STATIC_LIB_TARGET static)
SET(STATIC_LIB_NAME emojidex_static)

ADD_LIBRARY(${EMOJIDEX_STATIC_LIB_TARGET} ${EMOJIDEX_CPP_FILES})
TARGET_LINK_LIBRARIES(${EMOJIDEX_STATIC_LIB_TARGET} ${EMOJIDEX_LINK_LIBRARIES})

SET_TARGET_PROPERTIES(${EMOJIDEX_STATIC_LIB_TARGET}
	PROPERTIES
  #EXCLUDE_FROM_ALL TRUE
	POSITION_INDEPENDENT_CODE TRUE
	OUTPUT_NAME ${STATIC_LIB_NAME}
)

# Java port with SWIG
IF(JAVA)
	INCLUDE(${PROJECT_SOURCE_DIR}/interfaces/java/CMakeLists.txt)
ENDIF(JAVA)

IF(RUBY)
  INCLUDE(${PROJECT_SOURCE_DIR}/interfaces/ruby/CMakeLists.txt)
ENDIF(RUBY)

IF(OBJC)
  INCLUDE(${PROJECT_SOURCE_DIR}/interfaces/objc/CMakeLists.txt)
ENDIF(OBJC)

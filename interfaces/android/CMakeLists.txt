if (ANDROID)
  message(STATUS "Android Build Activated. Preparing build chain and deps.")
endif()

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -fno-strict-aliasing")
endif()

#Set natives build dir
# TODO change this!
SET(NATIVES_BUILD_DIR ${CMAKE_BINARY_DIR}/../tmp/build/)

#Get required libs/build chain tools
EXECUTE_PROCESS(COMMAND ruby interfaces/android/prepare.rb ${NATIVES_BUILD_DIR}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/interfaces/android/android-cmake/android.toolchain.cmake)
SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_POSITION_INDEPENDENT_CODE TURE)
SET(DO_DYNAMIC false)
SET(DO_INSTALL false)

SET(CMAKE_PREFIX_PATH ${NATIVES_BUILD_DIR}/natives/arm ${CMAKE_PREFIX_PATH})

SET(BOOST_LIBRARYDIR $ENV{CRYSTAX_NDK}/sources/boost/1.58.0/libs/armeabi-v7a/)
LINK_DIRECTORIES(${NATIVES_BUILD_DIR}/natives/arm/lib/
  ${BOOST_LIBRARYDIR}
  )

SET(BOOST_INCLUDEDIR $ENV{CRYSTAX_NDK}/sources/boost/1.58.0/include/)
INCLUDE_DIRECTORIES(BEFORE ${NATIVES_BUILD_DIR}/natives/arm/include/
  ${BOOST_INCLUDEDIR}
  )
LIST(APPEND CMAKE_MODULE_PATH "${NATIVES_BUILD_DIR}/natives/arm/lib/")

SET(BOOST_ROOT $ENV{CRYSTAX_NDK}/sources/boost/1.58.0/)
SET(USE_STATIC_BOOST ON)

#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(CMAKE_EXE_LINKER_FLAGS "-static")

#FIND_PACKAGE(SWIG REQUIRED)

SET(CMAKE_SWIG_FLAGS -package libemojidex)
SET(CMAKE_SWIG_OUTDIR "src")
SET_SOURCE_FILES_PROPERTIES("${PROJECT_SOURCE_DIR}/src/libemojidex.i"
	PROPERTIES
	CPLUSPLUS 1
)

SET(BUILD_TESTS false)

# TODO & TEMPFIX
# Running SWIG through CMAKE doesn't work because CMAKE SWIG is too tied to the base system.
# As a temporary fix the actual compilation is commented out and we're using a postbuild script
# to do the actual SWIG handling; passing SWIG generated interfaces through an android mk project.
ADD_CUSTOM_TARGET(android
	ruby interfaces/android/androidbuild.rb ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${NATIVES_BUILD_DIR}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Jar test
FIND_PACKAGE(Java REQUIRED COMPONENTS Runtime Development)
INCLUDE(UseJava)

SET(SWIG_ANDROID_JAR_TARGET android_jar)
SET(SWIG_ANDROID_JAR_NAME libemojidex-android)
SET(SWIG_ANDROID_JAR_FILENAME ${SWIG_ANDROID_JAR_NAME}-${EMOJIDEX_LIB_VERSION}.jar)
SET(EMOJIDEX_JAVA_FILES
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Client.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Data/Checksums.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Data/Collection.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Data/Emoji.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Data/MojiCodes.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/Indexes.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/Search.java
# ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/Settings.java
# ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/Transactor.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/EmojiVector.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/StringVector.java
# ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/LibEmojidex.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/LibEmojidexJNI.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/NativeLibLoader.java
)

CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/interfaces/android/src/NativeLibLoader.java.in ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/NativeLibLoader.java @ONLY)

ADD_JAR(${SWIG_ANDROID_JAR_TARGET}
  SOURCES ${EMOJIDEX_JAVA_FILES}
  VERSION ${EMOJIDEX_LIB_VERSION}
  OUTPUT_NAME ${SWIG_ANDROID_JAR_NAME}
)
SET_TARGET_PROPERTIES(${SWIG_ANDROID_JAR_TARGET}
  PROPERTIES
  EXCLUDE_FROM_ALL TRUE
)

ADD_DEPENDENCIES(${SWIG_ANDROID_JAR_TARGET} android)

ADD_CUSTOM_COMMAND(TARGET ${SWIG_ANDROID_JAR_TARGET}
  POST_BUILD
  COMMAND ${JAVA_ARCHIVE} -uvf ${SWIG_ANDROID_JAR_FILENAME} libs/
)

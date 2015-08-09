if (ANDROID)
  message(STATUS "Android Build Activated. Preparing build chain and deps.")
endif()

#Get required libs/build chain tools
EXECUTE_PROCESS(COMMAND ruby interfaces/android/prepare.rb ${CMAKE_BINARY_DIR}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/interfaces/android/android-cmake/android.toolchain.cmake)
SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_POSITION_INDEPENDENT_CODE TURE)
SET(DO_DYNAMIC false)
SET(DO_INSTALL false)

SET(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/natives/arm ${CMAKE_PREFIX_PATH})
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/natives/arm/lib/)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/natives/arm/include/)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/natives/arm/lib/")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(CMAKE_EXE_LINKER_FLAGS "-static")
#SET(BOOST_INCLUDEDIR ${CMAKE_BINARY_DIR}/Boost-for-Android/build/include/*/)
#SET(BOOST_LIBRARYDIR ${CMAKE_BINARY_DIR}/Boost-for-Android/build/lib/)
SET(BOOST_ROOT ${CMAKE_BINARY_DIR}/Boost-for-Android/build/)
SET(USE_STATIC_BOOST ON)

#FIND_PACKAGE(SWIG REQUIRED)

SET(CMAKE_SWIG_FLAGS -package libemojidex)
SET(CMAKE_SWIG_OUTDIR "src")
SET_SOURCE_FILES_PROPERTIES("${PROJECT_SOURCE_DIR}/src/libemojidex.i"
	PROPERTIES
	CPLUSPLUS 1
)

SET(BUILD_TESTS false)

# Java interface
#INCLUDE(${PROJECT_SOURCE_DIR}/interfaces/java/CMakeLists.txt)

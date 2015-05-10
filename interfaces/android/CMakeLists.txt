#Get required libs/build chain tools
EXECUTE_PROCESS(COMMAND ruby interfaces/android/prepare.rb ${CMAKE_BINARY_DIR}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_BUILD_TYPE Release) # Debugging to come later... maybe?


INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/interfaces/android/android-cmake/android.toolchain.cmake)

#FIND_PACKAGE(SWIG REQUIRED)
#SET(USE_STATIC_BOOST ON)

SET(BOOST_ROOT ${CMAKE_BINARY_DIR}/Boost-for-Android/build/)
SET(BOOST_INCLUDEDIR ${CMAKE_BINARY_DIR}/Boost-for-Android/build/include/*/)
SET(BOOST_LIBRARYDIR ${CMAKE_BINARY_DIR}/Boost-for-Android/build/lib/)

SET(CMAKE_SWIG_FLAGS -package libemojidex)
SET(CMAKE_SWIG_OUTDIR "src")
SET_SOURCE_FILES_PROPERTIES("${PROJECT_SOURCE_DIR}/src/libemojidex.i"
	PROPERTIES
	CPLUSPLUS 1
)

SET(BUILD_TESTS false)

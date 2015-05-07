#Get required libs/build chain tools
EXECUTE_PROCESS(COMMAND ruby interfaces/android/prepare.rb ${CMAKE_BINARY_DIR}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_BUILD_TYPE Release) # Debugging to come later... maybe?
SET(USE_STATIC_BOOST ON)

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/interfaces/android/android-cmake/android.toolchain.cmake)

SET(BOOST_INCLUDEDIR ${CMAKE_BINARY_DIR}/Boost-for-Android/build/include/*/)
SET(BOOST_LIBRARYDIR ${CMAKE_BINARY_DIR}/Boost-for-Android/build/lib/)


# Generate dynamic library
FIND_PACKAGE(Boost REQUIRED
	system
	filesystem
	)
FIND_PACKAGE(OpenSSL)

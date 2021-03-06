# Generate java sources and library with SWIG
FIND_PACKAGE(Java REQUIRED COMPONENTS Runtime Development)
FIND_PACKAGE(JNI REQUIRED)
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE_DIRECTORIES(${JNI_INCLUDE_DIRS})
INCLUDE(UseJava)
INCLUDE(UseSWIG)

SET(SWIG_JAVA_TARGET java)
SET(SWIG_JAVA_LIB_NAME emojidex_java)
SET(SWIG_JAVA_PACKAGE_NAME com.emojidex.libemojidex)

SET(CMAKE_JNI_TARGET TRUE)
SET(CMAKE_SWIG_FLAGS -package ${SWIG_JAVA_PACKAGE_NAME})
SET(CMAKE_SWIG_OUTDIR "com/emojidex/libemojidex")
SET_SOURCE_FILES_PROPERTIES("${PROJECT_SOURCE_DIR}/src/libemojidex.i"
	PROPERTIES
	CPLUSPLUS 1
)

SWIG_ADD_MODULE(${SWIG_JAVA_TARGET} java "${PROJECT_SOURCE_DIR}/src/libemojidex.i")
SWIG_LINK_LIBRARIES(${SWIG_JAVA_TARGET} ${EMOJIDEX_STATIC_LIB_TARGET})
SET_TARGET_PROPERTIES(${SWIG_JAVA_TARGET}
	PROPERTIES
	EXCLUDE_FROM_ALL TRUE
	OUTPUT_NAME ${SWIG_JAVA_LIB_NAME}
)

ADD_DEPENDENCIES(${SWIG_JAVA_TARGET} ${EMOJIDEX_STATIC_LIB_TARGET})


# Generate jar with SWIG
SET(SWIG_JAR_TARGET jar)
SET(SWIG_JAR_NAME libemojidex)
SET(SWIG_JAR_FILENAME ${SWIG_JAR_NAME}-${EMOJIDEX_LIB_VERSION}.jar)
SET(EMOJIDEX_JAVA_FILES
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Client.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Data/Checksums.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Data/Collection.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Data/Emoji.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Data/MojiCodes.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/Indexes.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/Search.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/QueryOpts.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/User.java
# ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/Settings.java
# ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/Transactor.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/Emojidex/Service/HistoryItem.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/EmojiVector.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/StringVector.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/HistoryItemVector.java
# ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/LibEmojidex.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/LibEmojidexJNI.java
  ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/LibemojidexInitializer.java
)

IF(WIN32)
	SET(SWIG_JAVA_LIB_FILENAME lib${SWIG_JAVA_LIB_NAME}.dll)
ELSEIF(APPLE)
	SET(SWIG_JAVA_LIB_FILENAME lib${SWIG_JAVA_LIB_NAME}.dylib)
ELSE(WIN32)
	SET(SWIG_JAVA_LIB_FILENAME lib${SWIG_JAVA_LIB_NAME}.so)
ENDIF(WIN32)

CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/interfaces/java/src/LibemojidexInitializer.java.in ${PROJECT_BINARY_DIR}/com/emojidex/libemojidex/LibemojidexInitializer.java @ONLY)

ADD_JAR(${SWIG_JAR_TARGET}
	SOURCES ${EMOJIDEX_JAVA_FILES}
	VERSION ${EMOJIDEX_LIB_VERSION}
	OUTPUT_NAME ${SWIG_JAR_NAME}
)
SET_TARGET_PROPERTIES(${SWIG_JAR_TARGET}
	PROPERTIES
	EXCLUDE_FROM_ALL TRUE
)

INSTALL_JAR(${SWIG_JAR_TARGET} ${LIB_INSTALL_DIR}/emojidex)
INSTALL_JNI_SYMLINK(${SWIG_JAR_TARGET} .)

ADD_DEPENDENCIES(${SWIG_JAR_TARGET} ${SWIG_JAVA_TARGET})

ADD_CUSTOM_COMMAND(TARGET ${SWIG_JAR_TARGET}
	POST_BUILD
	COMMAND ${JAVA_ARCHIVE} -uvf ${SWIG_JAR_FILENAME} ${SWIG_JAVA_LIB_FILENAME}
)

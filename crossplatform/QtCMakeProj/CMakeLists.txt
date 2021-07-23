cmake_minimum_required(VERSION 3.8)

MESSAGE("version: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
MESSAGE("version: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_TWEAK_VERSION}")
MESSAGE("version:${CMAKE_VERSION}")

 
PROJECT(QCityPlanApp VERSION 1.0.0  LANGUAGES CXX)

SET(CMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT TRUE)
SET(CMAKE_ECLIPSE_GENERATE_LINKED_RESOURCES FALSE)
# Check if we are doing out of source builds
STRING(COMPARE NOTEQUAL ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} CMAKE_OUT_OF_SOURCE_BUILD)

#if (NOT CMAKE_BUILD_TYPE)
#   set (CMAKE_BUILD_TYPE "Debug")
#   message (
#      STATUS "No CMAKE_BUILD_TYPE selected, defaulting to ${CMAKE_BUILD_TYPE}"
#   )
#endif ()
# Relative paths can be trouble when doing out of source builds
IF(CMAKE_OUT_OF_SOURCE_BUILD)
	SET(DEFAULT_RELATIVE_PATHS OFF)
ELSE()
	SET(DEFAULT_RELATIVE_PATHS ON)
ENDIF()
message("dddd:---" ${CMAKE_BUILD_TYPE})
# Show relative paths options 
OPTION(CMAKE_USE_RELATIVE_PATHS "If true, cmake will use relative paths in makefiles and projects." ${DEFAULT_RELATIVE_PATHS})
MARK_AS_ADVANCED(CMAKE_USE_RELATIVE_PATHS)


include_directories(${CMAKE_SOURCE_DIR}
 "${CMAKE_SOURCE_DIR}/include")
link_directories(${CMAKE_SOURCE_DIR}/lib)
include(${CMAKE_SOURCE_DIR}/cmake/utility.cmake)
set(T_OS WINDOWS)
set(T_PLATFORM x86)
if(WIN32)
	if (  CMAKE_CL_64)
		set(T_PLATFORM x64)	
	endif()
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(T_PLATFORM x64)	
endif()

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
	set(T_OS windows)
    Message("build cmake on windows platform")
elseif (CMAKE_HOST_APPLE)
    set(MACOS 1)
	set(T_OS macos)
    Message("build cmake on apple platform")
elseif (CMAKE_HOST_UNIX)
    set(LINUX 1)
	set(T_OS linux)
    Message("build cmake on UNIX/linux platform")
endif ()

    message(STATUS "linux path:"$ENV{PATH})
    message(STATUS "qt:"$ENV{QT_ROOT})
    message(STATUS "thirdparty:"$ENV{THIRDPAETY})
    set(THIRDPARTY_ROOT $ENV{THIRDPARTY_ROOT})
    set(QT_ROOT $ENV{QT_ROOT})
    message(STATUS "THIRDPARTY_ROOT:${THIRDPARTY_ROOT}")
    message(STATUS "QT_ROOT:${QT_ROOT}")	
if(WINDOWS)
    set(QT_QMAKE_EXECUTABLE ${QT_ROOT}/bin/qmake) 
    message("--windows--")
elseif(LINUX)
    set(QT_QMAKE_EXECUTABLE ${QT_ROOT}/bin/qmake) 
    message("--linux--")
endif()
    set (QT_ROOT "/opt/Qt5.12.10/5.12.10/gcc_64")
    set(CMAKE_PREFIX_PATH ${QT_ROOT})
    set(QT_DIR ${QT_ROOT}/lib/cmake/Qt5)
    set(Qt5Core_DIR ${QT_ROOT}/lib/cmake/Qt5Core) 
    set(Qt5Gui_DIR ${QT_ROOT}/lib/cmake/Qt5Gui) 
    set(Qt5Widgets_DIR ${QT_ROOT}/lib/cmake/Qt5Widgets) 
    set(Qt5_DIR ${QT_ROOT}/lib/cmake/Qt5 )
    message(${QT_DIR})

SET(OUTPUT_LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/${T_OS}/${T_PLATFORM})
SET(OUTPUT_BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/${T_OS}/${T_PLATFORM})


# SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})
# SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
# IF(WIN32)
# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
# ELSE(WIN32)
# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})
# ENDIF(WIN32)

#if(WINDOWS)


IF(CMAKE_VERSION VERSION_GREATER_EQUAL 2.6.0)
    # If CMake < 2.6.0
    SET(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BINDIR})
    SET(LIBRARY_OUTPUT_PATH    ${OUTPUT_LIBDIR})
ELSE()
    # If CMake >= 2.6.0
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
    IF(WIN32)
        SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
    ELSE(WIN32)
        SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})
    ENDIF(WIN32)

    # Testing CMAKE_VERSION is possible in >= 2.6.4 only
    # BUILDER_VERSION_GREATER(2 8 0)
     IF(VALID_BUILDER_VERSION)  # If CMake >= 2.8.1
         FOREACH(CONF ${CMAKE_CONFIGURATION_TYPES})       # For each configuration (Debug, Release, MinSizeRel... and/or anything the user chooses)
             STRING(TOUPPER "${CONF}" CONF)                # Go uppercase (DEBUG, RELEASE...)
             SET("CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}/${CONF}")
             SET("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_BINDIR}/${CONF}")
             IF(WIN32)
                 SET("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_BINDIR}/${CONF}")
             ELSE()
                SET("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}/${CONF}}")
            ENDIF()
			message("------------CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}  ${OUTPUT_LIBDIR}/${CONF}")
         ENDFOREACH()
     ENDIF(VALID_BUILDER_VERSION)
ENDIF()
#ENDIF(WINDOWS)

IF(MSVC)
	# Make sure we use minimal windows.h library without min max macros
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D \"WIN32_LEAN_AND_MEAN\"")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D \"NOMINMAX\"")

	# Use Link Time Code Generation
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG")

	OPTION(BUILD_MULTI_PROCESSOR_COMPILATION "Use multiple processors when compiling" ON)
	MARK_AS_ADVANCED(BUILD_MULTI_PROCESSOR_COMPILATION)

	IF(BUILD_MULTI_PROCESSOR_COMPILATION)
		# Set multi processor build
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	ENDIF(BUILD_MULTI_PROCESSOR_COMPILATION)
	# Set warnings to level 4 
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	IF (WARNINGS_AS_ERRORS)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
	ENDIF (WARNINGS_AS_ERRORS)
ENDIF(MSVC)


set(CMAKE_MODULE_PATH  ${QT_ROOT}/lib/cmake )
#list(APPEND CMAKE_PREFIX_PATH  ${QT_ROOT}/lib/cmake)
list(APPEND CMAKE_PREFIX_PATH ${THIRDPARTY_ROOT})
list(APPEND CMAKE_PREFIX_PATH ${THIRDPARTY_ROOT}/publish)


list(APPEND CMAKE_PREFIX_PATH ${THIRDPARTY_ROOT}/publish/${T_OS}/${T_PLATFORM}/Debug)
list(APPEND CMAKE_PREFIX_PATH ${THIRDPARTY_ROOT}/publish/${T_OS}/${T_PLATFORM}/Release)
#SET(OSG_DIR ${THIRDPARTY_ROOT}/publish/${T_OS}/${T_PLATFORM}/Debug)
#SET(OSG_ROOT ${THIRDPARTY_ROOT}/publish/${T_OS}/${T_PLATFORM}/Release)
#list(APPEND CMAKE_PREFIX_PATH ${THIRDPARTY_ROOT}/OSG/build)

#set(OpenSceneGraph_ROOT ${THIRDPARTY_ROOT}/publish/)
if(LINUX)
#set(OpenSceneGraph_ROOT ${THIRDPARTY_ROOT}/OSG/build)
endif()

message("----------${OpenSceneGraph_ROOT}")
#if(WINDOWS)
 if("${CMAKE_VERSION}" VERSION_GREATER_EQUAL 3.12.0)
	if(POLICY CMP0074)
    		cmake_policy(SET CMP0074 NEW) 
	endif()
endif()

if(POLICY CMP0072)
	cmake_policy(SET CMP0072 NEW)
endif()
#endif()

#add_subdirectory(src)

add_subdirectory(src/QCityPlanApp)
add_subdirectory(src/KernelCommon)
add_subdirectory(src/QtApp)
add_subdirectory(src/osgTest)

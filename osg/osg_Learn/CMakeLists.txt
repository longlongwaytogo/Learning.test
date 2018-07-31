# Osg learn examples
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)



#--------------------------------------------
#find_package( OpenThreads )
#find_package( osg )
#find_package( osgDB )
#find_package( osgUtil )
#find_package( osgViewer )
#macro( config_project PROJNAME LIBNAME )
#include_directories( ${${LIBNAME}_INCLUDE_DIR} )
#target_link_libraries( ${PROJNAME} ${${LIBNAME}_LIBRARY} )
#endmacro()
#add_executable( MyProject main.cpp )
#config_project( MyProject OPENTHREADS )
#config_project( MyProject OSG )
#config_project( MyProject OSGDB )
#config_project( MyProject OSGUTIL )
#config_project( MyProject OSGVIEWER )
#--------------------------------------------


#--------------------------------------------------------

#project OsgLearning
PROJECT(OsgLearning)

SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "E:\\project\\osg\\OpenSceneGraph-3.4.0\\qt_ms" "E:\\project\\osg\\OpenSceneGraph-3.4.0")
#add osg lib

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


FIND_PACKAGE(OpenSceneGraph 3.4.0 REQUIRED osgViewer osgDB osgGA osgUtil osgText)



#find_package(Qt5 COMPONENTS  QTOPENGL)
# add link lib



Message("lib dir:${OPENSCENEGRAPH_LIBRARY_DIRS}")
message("include dir:${OPENSCENEGRAPH_INCLUDE_DIRS}")
MESSAGE("lib:${OPENSCENEGRAPH_LIBRARIES}")
INCLUDE_DIRECTORIES(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
#link_libraries(osg osgDB osgUtil osgviewer openthreads)
LINK_LIBRARIES( ${OPENSCENEGRAPH_LIBRARIES} )

#add example subDirectory

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
#et( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/Bin)

add_executable("osgTest" "test/main.cpp")
add_subdirectory(code)



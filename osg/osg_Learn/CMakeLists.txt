# Osg learn examples
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#project OsgLearning
PROJECT(OsgLearning)

SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "E:\\project\\osg\\OpenSceneGraph-3.4.0\\qt_ms" "E:\\project\\osg\\OpenSceneGraph-3.4.0")
#add osg lib

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


FIND_PACKAGE(OpenSceneGraph 3.4.0 REQUIRED osgViewer osgDB osgGA osgUtil)



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



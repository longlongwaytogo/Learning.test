# Osg learn examples
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#project OsgLearning
PROJECT(OsgLearning)


#add osg lib
FIND_PACKAGE(OpenSceneGraph REQUIRED osgViewer osgDB osgGA osgUtil)

# add link lib

Message("lib dir:${OPENSCENEGRAPH_LIBRARY_DIR}")
message("include dir:${OPENSCENEGRAPH_INCLUDE_DIR}")
INCLUDE_DIRECTORIES(${OPENSCENEGRAPH_INCLUDE_DIR})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIR})
#link_libraries(osg osgDB osgUtil osgviewer openthreads)
LINK_LIBRARIES( ${OPENSCENEGRAPH_LIBRARIES} )

#add example subDirectory


add_executable("osgTest" "test/main.cpp")
add_subdirectory(code)


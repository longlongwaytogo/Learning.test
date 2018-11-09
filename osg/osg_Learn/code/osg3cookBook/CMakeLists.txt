#ch01
SET(osg3book "osg3CookBook")

MACRO(createPrj prjName file)

ADD_EXECUTABLE(${prjName} ${file})
TARGET_LINK_LIBRARIES(${prjName} osgComm)
SET_TARGET_PROPERTIES(${prjName} PROPERTIES FOLDER "${osg3book}") 
ENDMACRO()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/comm)

#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)


ADD_LIBRARY(osgComm STATIC comm/comm.h comm/comm.cpp)
SET_TARGET_PROPERTIES(osgComm PROPERTIES FOLDER "${osg3book}") 

#ADD_EXECUTABLE(ch01-01-Geometry ch01/geometry.cpp)
#SET_TARGET_PROPERTIES(ch01-01-Geometry PROPERTIES FOLDER "${osg3book}")
#ch01
createPrj(ch01-01-Geometry ch01/geometry.cpp)

#ch02
createPrj(ch02-01-observer_ptr ch02/observer_ptr.cpp)
createPrj(ch02-02-clone_objects ch02/clone_objects.cpp)
createPrj(ch02-03-bounding_box ch02/bounding_box.cpp)

#ch01
SET(osg3book "osg3CookBook")
ADD_EXECUTABLE(ch01-01-Geometry ch01/geometry.cpp)
MESSAGE(${CMAKE_DEBUG_POSTFIX})
SET_TARGET_PROPERTIES(ch01-01-Geometry PROPERTIES FOLDERS "${osg3book}")
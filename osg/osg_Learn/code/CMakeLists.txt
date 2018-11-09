
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${PROJECT_SOURCE_DIR})
message(${CMAKE_CURRENT_BINARY_DIR})
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/osgCamera"  ${CMAKE_CURRENT_BINARY_DIR}/"osgCamera.dir")

#add_executable("osgCamera" osgCamera/main.cpp)


add_subdirectory(osg3Guide)

add_subdirectory(osgCamera)
add_subdirectory(osgPagedLod)
add_subdirectory(osgPick)
add_subdirectory(osgCallback)

# Qt test
add_subdirectory(osgQtApp)
add_subdirectory(osgViewerMFC)
#add_subdirectory(osgViewerQt)
# add_subdirectory(osgQtWidgets)
add_subdirectory(osgqFont)
# add_subdirectory(osgQtBrowser)
#add_subdirectory(osgQtGraphicView)

# cookbook 
add_subdirectory(osg3cookBook)
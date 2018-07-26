Set(subProjName "osgQtApp")


#FIND_PACKAGE(OpenSceneGraph REQUIRED osgViewer osgDB osgGA osgUtil osgQt)

#INCLUDE_DIRECTORIES(${OPENSCENEGRAPH_INCLUDE_DIR})
#link_directories(${OPENSCENEGRAPH_LIBRARY_DIR})
#link_libraries(osg osgDB osgUtil osgviewer openthreads)
#LINK_LIBRARIES( ${OPENSCENEGRAPH_LIBRARIES} )

# Qt creator fix
#add_definitions(-DQT_CREATOR_FIX_COMPILE)



FIND_PACKAGE(osgQt)
FIND_PACKAGE(Qt5Widgets REQUIRED QT5OPENGL)
FIND_PACKAGE(Qt5OpenGL REQUIRED)


INCLUDE_DIRECTORIES(${OSGQT_INCLUDE_DIR})
link_directories(${OSGQT_LIBRARY_DIR})
LINK_LIBRARIES( ${OSGQT_LIBRARIES} )

INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})
LINK_DIRECTORIES(${Qt5Widgets_LIBRARY_DIR})
LINK_LIBRARIES(${Qt5Widgets_LIBRARIES})


INCLUDE_DIRECTORIES(${Qt5OpenGL_INCLUDE_DIR})
MESSAGE( STATUS  "Qt5OpenGL_dir: ${Qt5OpenGL_INCLUDE_DIRS}" )
MESSAGE( STATUS  "Qt5Widgets_INCLUDE_DIR: ${Qt5Widgets_INCLUDE_DIRS}" )
#INCLUDE_DIRECTORIES("D:\\Qt\\Qt5.6.1\\5.6\\msvc2015_64\\include\\QtOpenGL")
LINK_DIRECTORIES(${Qt5OpenGL_LIBRARY_DIR})
LINK_LIBRARIES(${Qt5OpenGL_LIBRARIES})
aux_source_directory(. SRC)
SET(SourceGroup_Sky "${CMAKE_CURRENT_SOURCE_DIR}/skyBox.h" "${CMAKE_CURRENT_SOURCE_DIR}/skyBox.cpp")
#SET(SourceGroup_Sky "skyBox.h" "skyBox.cpp")
MESSAGE("sourceGroup:${SourceGroup_Sky}")
SOURCE_GROUP(Sky FILES ${SourceGroup_Sky})
add_executable(${subProjName} ${SourceGroup_Sky} ${SRC}  )

SET_TARGET_PROPERTIES(${subProjName} PROPERTIES FOLDER "QtApp")



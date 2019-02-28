#ch01
SET(osg3book "osg3CookBook")

MACRO(createPrj prjName file)
MESSAGE(${file})
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


#ch03
createPrj(ch03-03-NurbsSurface ch03/NurbsSurface.cpp)
TARGET_LINK_LIBRARIES(ch03-03-NurbsSurface opengl32.lib glu32.lib)
createPrj(ch03-10-draw_instance ch03/draw_instance.cpp)
createPrj(ch03-11-clock_face ch03/clock_face.cpp)
createPrj(ch03-12-dynamic_ribbon ch03/dynamic_ribbon.cpp)
createPrj(ch03-13-select_model ch03/select_model.cpp)
createPrj(ch03-14-select_face ch03/select_face.cpp)
createPrj(ch03-15-select_point ch03/select_point.cpp)
createPrj(ch03-17-vertex_displacement ch03/vertex_displacement.cpp)


# ch04 
createPrj(ch04-01-multiple-screen ch04/multiple_screen)
createPrj(ch04-02-power-wall ch04/power_wall.cpp)


#ch08
createPrj(ch08-01-merge-geometry ch08/merge_geom.cpp)
createPrj(ch08-02-compress-texture ch08/compress_texture.cpp)
createPrj(ch08-03-share-objects ch08/share_objects.cpp)
createPrj(ch08-04-config-pager ch08/config_pager.cpp)
createPrj(ch08-05-Maze-cull ch08/Maze.cpp)

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

# ch09
createPrj(ch09-01-osgQt ch09/osg_qt.cpp)

#ch10

createPrj(ch10-01-delaunay-triangulator ch10/delaunay.cpp)
SET(file ch10/SIMP_Main.cpp ch10/SIMP_ReaderWriter.h ch10/SIMP_ReaderWriter.cpp)
createPrj(ch10-02-simp-loader ${file})
#ADD_LIBRARY(osgdb_simp ch10/SIMP_ReaderWriter.cpp)

createPrj(ch10-03-meta-data ch10/meta_data.cpp)


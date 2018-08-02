Set(subProjName "osg3_4_Geometry")

find_package( glut )
#-------------------------------------------------------------
macro( config_project PROJNAME LIBNAME )
include_directories( ${${LIBNAME}_INCLUDE_DIR} )
target_link_libraries( ${subProjName} ${${LIBNAME}_LIBRARY} )
endmacro()

#-------------------------------------------------------------


aux_source_directory(. SRC)
add_executable(${subProjName} ${SRC} )

config_project( MyProject GLUT )
SET_TARGET_PROPERTIES(${subProjName} PROPERTIES FOLDER "osg3Guide")
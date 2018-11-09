Set(subProjName "osg3_6_RenderEffect")


#-------------------------------------------------------------
macro( config_project PROJNAME LIBNAME )
include_directories( ${${LIBNAME}_INCLUDE_DIR} )
target_link_libraries( ${subProjName} ${${LIBNAME}_LIBRARY} )
endmacro()

#-------------------------------------------------------------


aux_source_directory(. SRC)
add_executable(${subProjName} ${SRC} )


SET_TARGET_PROPERTIES(${subProjName} PROPERTIES FOLDER "osg3Guide")
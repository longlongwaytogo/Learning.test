


 if("${CMAKE_VERSION}" VERSION_GREATER_EQUAL 3.12.0)
	if(POLICY CMP0074)
    		cmake_policy(SET CMP0074 NEW) 
	endif()
endif()

FIND_PACKAGE( OpenGL REQUIRED )

FIND_PACKAGE( OpenSceneGraph REQUIRED osgViewer osgDB osgGA osgUtil osgText)


SET(TARGET_NAME osgTest)

IF(OPENSCENEGRPAH_FOUND)
    MESSAGE( STATUS "not find osg lib")

ELSEIF()
    MESSAGE(FATAL_ERROR "find osg lib")
ENDIF()

INCLUDE_DIRECTORIES(
    ${OPENGL_INCLUDE_DIR}
    ${OPENSCENEGRAPH_INCLUDE_DIR} /usr/local/include
)


message(" linux inc:${OPENSCENEGRAPH_INCLUDE_DIR}" )
message(" linux lib:${OPENSCENEGRAPH_LIBRARIES}" )
ADD_EXECUTABLE(${TARGET_NAME} main.cpp)


target_include_directories(${TARGET_NAME} PRIVATE
${OPENGL_INCLUDE_DIR}
${OPENSCENEGRAPH_INCLUDE_DIR}
/usr/local/include )

# Link to OpenSceneGraph libs
TARGET_LINK_LIBRARIES(${TARGET_NAME} ${OPENSCENEGRAPH_LIBRARIES})

message("osgRoot:${OpenSceneGraph_ROOT}")
#set(osgRunPath "PATH=${OpenSceneGraph_ROOT}/bin;%PATH%" )
if(MSVC)
set(osgRunPath "PATH=${THIRDPARTY_ROOT}/publish/${T_OS}/${T_PLATFORM}/${CMAKE_CFG_INTDIR}/bin;%PATH%" )

set_target_properties(${TARGET_NAME} PROPERTIES 
VS_DEBUGGER_ENVIRONMENT "${osgRunPath}"
VS_DEBUGGER_COMMAND_ARGUMENTS "cow.osg")
endif()

#set_target_properties(${TARGET_NAME}  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)"
#                                         VS_DEBUGGER_COMMAND                    "$(TargetPath)"
##                                       S_DEBUGGER_ENVIRONMENT             
#                                      "${THIRDPARTY_ROOT}/publish/${T_OS}/${T_PLATFORM}/${CMAKE_CFG_INTDIR}/bin;%PATH%")

message("buildType:" ${CMAKE_BUILD_TYPE})


# Link to open gl libs
#TARGET_LINK_LIBRARIES(${TARGET_NAME} ${OPENGL_LIBRARIES} )



SET(VALID_BUILDER_VERSION OFF)
MACRO(BUILDER_VERSION_GREATER MAJOR_VER MINOR_VER PATCH_VER)
    SET(VALID_BUILDER_VERSION OFF)
    IF(CMAKE_MAJOR_VERSION GREATER ${MAJOR_VER})
        SET(VALID_BUILDER_VERSION ON)
    ELSEIF(CMAKE_MAJOR_VERSION EQUAL ${MAJOR_VER})
        IF(CMAKE_MINOR_VERSION GREATER ${MINOR_VER})
            SET(VALID_BUILDER_VERSION ON)
        ELSEIF(CMAKE_MINOR_VERSION EQUAL ${MINOR_VER})
            IF(CMAKE_PATCH_VERSION GREATER ${PATCH_VER})
                SET(VALID_BUILDER_VERSION ON)
            ENDIF(CMAKE_PATCH_VERSION GREATER ${PATCH_VER})
        ENDIF()
    ENDIF()
ENDMACRO(BUILDER_VERSION_GREATER MAJOR_VER MINOR_VER PATCH_VER)

# CMAKE24: if CMake version is <2.6.0.
SET(CMAKE24 OFF)
IF(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} LESS 5)
    SET(CMAKE24 ON)
ENDIF(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} LESS 5)

# CMAKE_VERSION_TEST: Define whether "IF(${CMAKE_VERSION} VERSION_LESS "x.y.z")" can be used or not.
BUILDER_VERSION_GREATER(2 6 3)
SET(CMAKE_VERSION_TEST ${VALID_BUILDER_VERSION})        # >= 2.6.4

SET(VALID_BUILDER_VERSION OFF)


#  create comm shared/static library
MACRO(CreateLib TargetName Shared_or_Static)

File(GLOB )
add_library(${TargetName} )


ENDMACRO(CreateLib TargetName Shared_or_Static)

# create qt comm shared/static library

# create consle App


# create QtApp
# 宏函数名称：CreateQtApp
# 工程名称：TargetName
# 所属层级： Layer
MACRO(CreateQtApp TargetName Layer)

    SET(CMAKE_INCLUDE_CURRENT_DIR ON)

    SET(CMAKE_AUTOUIC ON)
    SET(CMAKE_AUTOMOC ON)
    SET(CMAKE_AUTORCC ON)

    SET(CMAKE_CXX_STANDARD 11)
    SET(CMAKE_CXX_STANDARD_REQUIRED ON)

 
    #if(WINDOWS)
 if("${CMAKE_VERSION}" VERSION_GREATER_EQUAL 3.12.0)
	if(POLICY CMP0074)
    		cmake_policy(SET CMP0074 NEW) 
	endif()
endif()

    LIST (APPEND CMAKE_PREFIX_PATH $ENV{QT5_ROOT})

    FIND_PACKAGE(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
    FIND_PACKAGE(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

    FILE(GLOB HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
     ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_SOURCE_DIR}/${TargetName}/*.hpp
    ${CMAKE_SOURCE_DIR}/${TargetName}/*.h)

    FILE(GLOB CPP 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.CPP
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/*.CXX
    )

    FILE(GLOB UI
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/*.UI)

    FILE(GLOB QRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.QRC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

    
    SOURCE_GROUP("inc" FILES ${HEADERS})
    SOURCE_GROUP("src" FILES ${CPP})
    SOURCE_GROUP("ui" FILES ${UI})
    SOURCE_GROUP("res" FILES ${QRC})

    message(${UI} ${res} ${QRC} )

    ADD_EXECUTABLE(${TargetName} ${HEADERS} ${CPP} CMakeLists.txt ${UI} ${QRC})

    SET_PROPERTY(TARGET ${TargetName} PROPERTY FOLDER  ${Layer})


    #TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}}" debug "${${varname}_DEBUG}" release "${varname}")
    MESSAGE("-------------------------${CMAKE_SOURCE_DIR}/tools/linuxDeploy/linuxdeployqt.AppImage ARGS ${CMAKE_SOURCE_DIR}/bin/${T_PLATFORM}/${T_OS}/${CMAKE_CFG_INTDIR}/${TargetName} -appimage")
    MESSAGE(".${CMAKE_SOURCE_DIR}/tools/linuxDeploy/deploy.sh ${CMAKE_SOURCE_DIR}/tools/linuxDeploy/linuxdeployqt.AppImage ${CMAKE_SOURCE_DIR}/bin/${T_PLATFORM}/${T_OS}/${TargetName} -appimage")
    IF(WINDOWS)
        #add_custom_command(QtApp    POST_BUILD  COMMAND  echo ${TargetName})
        ADD_CUSTOM_COMMAND( TARGET ${TargetName} POST_BUILD  
                            COMMAND    windeployqt  ${CMAKE_SOURCE_DIR}/bin/${T_PLATFORM}/${T_OS}/${CMAKE_CFG_INTDIR}/${TargetName}.exe
         )
 
    ELSEIF(LINUX)
        #add_custom_command( TARGET ${TargetName} POST_BUILD
        #COMMAND .${CMAKE_SOURCE_DIR}/tools/linuxDeploy/deploy.sh ${CMAKE_SOURCE_DIR}/tools/linuxDeploy/linuxdeployqt.AppImage ${CMAKE_SOURCE_DIR}/bin/${T_PLATFORM}/${T_OS}/${TargetName} -appimage)
         #COMMAND  chomod +x ${CMAKE_SOURCE_DIR}/tools/linuxDeploy/linuxdeployqt.AppImage
         #COMMAND  ${CMAKE_SOURCE_DIR}/tools/linuxDeploy/linuxdeployqt.AppImage ${CMAKE_SOURCE_DIR}/bin/${T_PLATFORM}/${T_OS}/${CMAKE_CFG_INTDIR}/${TargetName} -appimage)
        #COMMAND  ${CMAKE_SOURCE_DIR}/tools/linuxDeploy/linuxdeployqt.AppImage ${CMAKE_SOURCE_DIR}/bin/${T_PLATFORM}/${T_OS}/${TargetName} -appimage )
    ENDIF()       

ENDMACRO(CreateQtApp TargetName Layer)


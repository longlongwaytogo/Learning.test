# Required variables:
# - SOURCE_FILES/HEADER_FILES/RESOURCE_FILES
# - EFFECT_FILES/POST_PROCESSORS/UI_FILES

MACRO(SETUP_TUTORIAL EXE_NAME FOLDER_)
	SOURCE_GROUP("Source Files" FILES ${SOURCE_FILES})
		SOURCE_GROUP("Header Files" FILES ${HEADER_FILES})
		SOURCE_GROUP("Resource Files" FILES ${RESOURCE_FILES})
		SOURCE_GROUP("Effect Files" FILES ${EFFECT_FILES})
		SOURCE_GROUP("Post Processors" FILES ${POST_PROCESSORS})
		SOURCE_GROUP("UI Files" FILES ${UI_FILES})

	ADD_EXECUTABLE(
	${EXE_NAME} 
	${SOURCE_FILES}
	${HEADER_FILES}
	${RESOURCE_FILES}
	${EFFECT_FILES} 
	${POST_PROCESSORS}
	${UI_FILES}
	)
	set_target_properties(${EXE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${KLAYGE_ROOT}/KlayGE/bin/win_x64"
                                            #   VS_DEBUGGER_COMMAND           "$<TARGET_FILE:${EXE_NAME}>"
											 VS_DEBUGGER_COMMAND           ""
                                               VS_DEBUGGER_ENVIRONMENT       "${MY_PATH}")


	SET_PROPERTY(TARGET ${EXE_NAME}  PROPERTY FOLDER ${FOLDER_})
	add_definitions(-DCURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

ENDMACRO()

add_custom_target("samples" SOURCES  CMakeLists.txt )
SET_PROPERTY(TARGET "samples" PROPERTY FOLDER CMakePredefinedTargets)


add_subdirectory(Tutor1)
add_subdirectory(Tutor2)
add_subdirectory(DrawAxis)
add_subdirectory(InputCaps)




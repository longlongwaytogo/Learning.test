add_executable(Tutor1
main.cpp
TutorFramework.h
TutorFramework.cpp
)
	SET(TargetName Tutor1)
	set_target_properties(${TargetName} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${KLAYGE_ROOT}/KlayGE/bin/win_x64"
                                               VS_DEBUGGER_COMMAND           "$<TARGET_FILE:${TargetName}>"
                                               VS_DEBUGGER_ENVIRONMENT       "${MY_PATH}")


	SET_PROPERTY(TARGET ${TargetName} PROPERTY FOLDER Tutorials)
	# SET_TARGET_PROPERTIES(${TargetName} PROPERTIES VS_DEBUGGER_ENVIRONMENT "${MY_PATH}")

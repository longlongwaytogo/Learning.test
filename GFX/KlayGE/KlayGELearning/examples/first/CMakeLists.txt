add_executable(first
main.cpp
TutorFramework.h
TutorFramework.cpp
)
	SET(TargetName first)
	set_target_properties(${TargetName} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${KLAYGE_ROOT}/KlayGE/bin/win_x64"
                                               VS_DEBUGGER_COMMAND           "$<TARGET_FILE:${TargetName}>"
                                               VS_DEBUGGER_ENVIRONMENT       "${MY_PATH}")

	SET_PROPERTY(TARGET ${TargetName} PROPERTY FOLDER ${package})
	# SET_TARGET_PROPERTIES(${TargetName} PROPERTIES VS_DEBUGGER_ENVIRONMENT "${MY_PATH}")
	add_definitions(-DKLAYGE_ROOT="${KLAYGE_ROOT}")
	add_definitions(-DKLAYGE_BINARY_ROOT="${KLAYGE_ROOT}/bin/win_x64")
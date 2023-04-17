SET(SOURCE_FILES
InputCaps.cpp
)

SET(HEADER_FILES
	InputCaps.hpp
)

SET(UI_FILES
InputCaps.uiml
)



SETUP_TUTORIAL(InputCaps "Tutorials")
target_link_libraries(InputCaps  ${KLAYGE_ROOT}/KlayGE/lib/win_x64/KlayGE_Core_vc142_d.lib)

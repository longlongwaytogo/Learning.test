# WxWidget Learning test

PROJECT(Learning_WxWidgets)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
FIND_PACKAGE(wxWidgets COMPONENTS gl core base OPTIONAL_COMPONENTS net)
	IF(wxWidgets_FOUND)
		INCLUDE("${wxWidgets_USE_FILE}")
	   #TARGET_LINK_LIBRARIES(MyTest ${wxWidgets_LIBRARIES})
		message(${wxWidgets_LIBRARIES})
		
		ADD_SUBDIRECTORY(test)
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	ELSE()
		MESSAGE("Not find WxWidget lib")
	ENDIF()
	
	

# SET(WX_INC_DIR CACHE PATH "include_dir")
# INCLUDE_DIRECTORIES(${WX_INC_DIR})



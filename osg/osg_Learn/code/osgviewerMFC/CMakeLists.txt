SET(TARGET_SRC MFC_OSG_MDI.cpp MFC_OSG_MDI.rc MFC_OSG_MDIDoc.cpp MFC_OSG_MDIView.cpp stdafx.cpp MFC_OSG.cpp MainFrm.cpp ChildFrm.cpp)
SET(TARGET_H   MFC_OSG_MDI.h   MFC_OSG_MDIDoc.h   MFC_OSG_MDIView.h   stdafx.h   MFC_OSG.h   MainFrm.h   ChildFrm.h Resource.h)

ADD_DEFINITIONS(-D_AFXDLL)
SET(REQUIRE_WINMAIN_FLAG 1)

 
#INCLUDE_DIRECTORIES("$ENV{VCInstallDir}atlmfc/include")
#MESSAGE("$ENV{VCInstallDir}atlmfc/include")
#LINK_DIRECTORIES("$ENV{VCInstallDir}atlmfc/lib/amd64")
INCLUDE_DIRECTORIES("D:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\VC\\atlmfc\\include")
LINK_DIRECTORIES("D:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\VC\\atlmfc/lib/amd64")         
#### end var setup  ###
MESSAGE("include:$ENV{VCInstallDir}atlmfc/include")
MESSAGE("lib:$ENV{VCInstallDir}atlmfc/lib/amd64")
ADD_EXECUTABLE(osgviewerMFC  WIN32 ${TARGET_SRC} ${TARGET_H})

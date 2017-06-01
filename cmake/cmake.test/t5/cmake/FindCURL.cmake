# find curl

SET(CURL_INC "D:\\vcpkg-master\\vcpkg\\installed\\x86-windows\\include")
SET(CURL_LIB "D:\\vcpkg-master\\vcpkg\\installed\\x86-windows\\lib")

MESSAGE(${CURL_INC})
MESSAGE(${CURL_LIB})

find_path(CURL_INCLUDE_DIR CURL\\curl.h ${CURL_INC} )
find_library(CURL_LIBRARY libcurl_imp.lib ${CURL_LIB})

MESSAGE(STATUS "-----------CURL INCLUDE: ${CURL_INCLUDE_DIR}")
MESSAGE(STATUS "-----------CURL LIBRARY: ${CURL_LIBRARY}")

IF(CURL_INCLUDE_DIR AND CURL_LIBRARY)
SET(CURL_FOUND TRUE)
MESSAGE("FIND CURL LIB")
ENDIF(CURL_INCLUDE_DIR AND CURL_LIBRARY)

IF(NOT CURL_FOUND)
 MESSAGE(FATAL_ERROR,"COULD NOT FIND CURL LIB")
 ENDIF(NOT CURL_FOUND)
 
 



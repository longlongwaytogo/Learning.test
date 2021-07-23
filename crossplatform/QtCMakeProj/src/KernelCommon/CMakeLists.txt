
aux_source_directory(. src)


add_definitions(-DEXPORT_KERNELCOMMON)
 
include_directories(${CMAKE_SOURCE_DIR}/include/KernelCommon)
add_library(KernelCommon SHARED ${src} Common.cpp )

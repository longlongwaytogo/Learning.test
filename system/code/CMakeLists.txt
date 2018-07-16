set(comm_Group "comm/SRWLock.h"
			"comm/SRWLock.cpp"

)
set(src_Group ${comm_Group} "main.cpp")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

source_group("comm" FILES ${comm_Group})
add_executable(testThread   ${src_Group})



message(${CMAKE_CURRENT_SOURCE_DIR})
message(${PROJECT_SOURCE_DIR})
message(${CMAKE_CURRENT_BINARY_DIR})
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/osgCamera"  ${CMAKE_CURRENT_BINARY_DIR}/"osgCamera.dir")

add_executable("osgCamera" osgCamera/main.cpp)
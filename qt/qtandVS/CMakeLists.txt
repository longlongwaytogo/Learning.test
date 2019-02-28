project(qtandVS)
cmake_minimum_required(VERSION 2.8.9)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

aux_source_directory(. SRC_LIST)
set(EXECUTABLE_OUTPUT_PATH  "${PROJECT_SOURCE_DIR}/bin")

set(CMAKE_MODULE_PATH "D:\\Qt\\Qt5.6.1\\5.6\\msvc2015_64\\lib\\cmake")
# Find the QtWidgets library
find_package(Qt REQUIRED QtCore QtGui QtXml)
link_directories("D:\\Qt\\Qt5.6.1\\5.6\\msvc2015_64\\lib")
include_directories("D:\\Qt\\Qt5.6.1\\5.6\\msvc2015_64\\include")
link_libraries("Qt5Widgetsd.lib" "Qt5UiToolsd.lib" "Qt5Cored.lib" "*.lib")


add_executable(${PROJECT_NAME} ${SRC_LIST})






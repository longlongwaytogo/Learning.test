CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(TestQWindow)


# 包含当前目录文件
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# 开启自动编译QT资源
SET(CMAKE_AUTOMOC ON)
#SET(CMAKE_AUTOUIC ON)   
#SET(CMAKE_AUTORCC ON)

# find qt5 
#find_package(Qt5 REQUIRED Widgets)
find_package(Qt5Widgets)

SET(QRC_FILES res.qrc)
SET(UI_FILES MainWindow.ui)

# consle 
SET(QT_USE_QTMAIN TRUE)

qt5_wrap_ui(ALL_UI ${UI_FILES})
qt5_add_resources(ALL_QRC ${QRC_FILES})

# files
aux_source_directory(. SRC_FILES)

# 生成exe 添加 WIN32，可以禁用默认生产的控制台窗口
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES} ${ALL_UI} ${ALL_QRC} )

#link 

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)



# 设置工程名称
SET(TargetName QtApp)

#find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# 创建Qt应用工程
CreateQtApp(${TargetName} "app") 

# 链接本项目内部
target_link_libraries(${TargetName} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets KernelCommon)

            
# 链接其他库文件
#target_link_libraries(${TargetName} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets KernelCommon)

学习参考：
https://github.com/carl-wang-cn/demo.git/cmake  <<CMake practise>>
https://github.com/wzpan/cmake-demo.git     <<Cmake 入门实战>>

t1:
PROJECT/MESSAGE/ADD_EXECUTABLE 命令 PROJECT_BINARY_DIR和PROJECT_SOURCE_DIR变量学习
t2:
ADD_SUBDIRECTORY、AUX_SOURCE_DIRECTORY 命令 EXECUTABLE_OUTPUT_PATH(输出路径设置) 变量 学习
t3:
ADD_LIBRARY 命令使用：
# 添加导出库，自动回添加 HELLO_SHARED_EXPORTS 宏，所以代码中可以判断这个条件
ADD_LIBRARY(HELLO_SHARED SHARED ${SRC_LIST}) 
ADD_LIBRARY(HELLO_STATIC STATIC ${SRC_LIST})
# 设置输出lib名称
SET_TARGET_PROPERTIES(HELLO_STATIC PROPERTIES OUTPUT_NAME "HELLO_static")
SET_TARGET_PROPERTIES(HELLO_SHARED PROPERTIES OUTPUT_NAME "HELLO")
t4:
TARGET_LINK_LIBRARIES 连接外部库； LINK_DIRECTORIES 添加外部库目录；INCLUDE_DIRECTORIES 外部头文件包含路径
t5: 
CMAKE_MODULE_PATH：设置module路径；FIND_PACKAGE 使用，FindCURL.cmake 编写和find_xx函数使用
t6: 
find功能加强训练
t7: 
configure_file 命令和 foreach测试\ CheckFunctionExists用法
link： http://hahack.com/codes/cmake/
掌握重点：
configure_file 用法
#cmakedefine 宏翻译后 会出现一些细节需要注意：
第一次编译(奇数)： #cmakedefine USE_OPTION --> #define USE_OPTION
第二次编译（偶数）：  #cmakedefine USE_OPTION -->/* #undef USE_OPTION */

t8:安装\测试\宏
link:https://gitlab.kitware.com/cmake/cmake/tree/master/Tests/Tutorial
link:http://hahack.com/codes/cmake/
CMAKE执行安装的流程是：
cmakelists.txt 编写安装脚本
cmakelists.txt 经过配置，会生成cmake_install.cmake 脚本文件
可以在控制台中执行 cmake.exe -p cmake_install.cmake 执行安装
如果使用gui工具生成vs的工程，会单独有个install的工程，工程的生成后事件会执行cmake.exe -p cmake_install.cmake 命令

如果使用nmake生成工程后，执行安装脚本需要调用nmake install命令，则会安装到指定目录下

SET(CMAKE_INSTALL_PREFIX "D:\\T8") 可以设置安装路径，次命令需要在 install命令之前调用有效，且

test命令，也会生成对应的.cmake 脚本，生成vs项目，则会出现test工程，其生成后事件会运行该脚本脚本 
（C:\Program Files\CMake\bin\ctest.exe  ctest.exe 默认调用CTestTestfile.cmake 脚本）

t9：版本、 安装包
制作安装包，需要安装NSIS打包工具进行打包
编译脚本后，也可通过命令打包：
生成二进制安装包：	
cpack -C CPackConfig.cmake
生成源码安装包：
cpack -C CPackSourceConfig.cmake

t10 生成源文件：




find_package 资料：http://blog.csdn.net/bytxl/article/details/50637277

command ：   http://blog.csdn.net/kl222/article/details/8258811
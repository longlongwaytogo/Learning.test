CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(T3)
#若变量build_shared_lib 没有设置，并且在add_library 时没有指定类型，默认生成的都是静态库
ADD_SUBDIRECTORY(LIB_HELLO)
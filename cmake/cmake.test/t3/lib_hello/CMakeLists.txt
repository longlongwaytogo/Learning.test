﻿AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_LIBRARY(HELLO_SHARED SHARED ${SRC_LIST}) # 添加导出库，自动回添加 HELLO_SHARED_EXPORTS 宏，所以代码中可以判断这个条件
ADD_LIBRARY(HELLO_STATIC STATIC ${SRC_LIST})

SET_TARGET_PROPERTIES(HELLO_STATIC PROPERTIES OUTPUT_NAME "HELLO_static")
SET_TARGET_PROPERTIES(HELLO_SHARED PROPERTIES OUTPUT_NAME "HELLO")
#ADD_DEFINITIONS(-DEXPORT_HELLO)

#设置版本号
SET_TARGET_PROPERTIES(HELLO_SHARED PROPERTIES VERSION 1.2 SOVERSION 1)

# 如果发现后来生成的lib清除了同名的早先生成的lib，（只有一个静态库或动态库生成）
# 试下下面两个命令
# 较新版本的cmake不再需要下面两个命令就可以同时生成hello.so hello.a
 SET_TARGET_PROPERTIES(HELLO_SHARED PROPERTIES CLEAN_DIRECT_OUTPUT 1)
 SET_TARGET_PROPERTIES(HELLO_STATIC PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/LIB)
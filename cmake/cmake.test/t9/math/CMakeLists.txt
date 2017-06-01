CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)

# 指定生成 MathFunctions 链接库
ADD_LIBRARY(MathFunctions ${DIR_LIB_SRCS})

# 设置安装路径
#SET(CMAKE_INSTALL_PREFIX "D:\\T9")

# 指定 MathFunctions 库的安装路径
INSTALL (TARGETS MathFunctions DESTINATION bin)
INSTALL (FILES MathFunctions.h DESTINATION include)





CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
ADD_EXECUTABLE(MakeTable MakeTable.cxx)

ADD_CUSTOM_COMMAND(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	DEPENDS MakeTable
)

# 指定生成 MathFunctions 链接库
add_library(MathFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h  )

# 设置安装路径
#SET(CMAKE_INSTALL_PREFIX "D:\\T10")

# 指定 MathFunctions 库的安装路径
INSTALL (TARGETS MathFunctions DESTINATION bin)
INSTALL (FILES MathFunctions.h DESTINATION include)





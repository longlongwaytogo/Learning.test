# CMake 最低版本要求
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(VERSION_MAXJOR 1)
SET(VERSION_MINJOR 0)



set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)


#项目信息
PROJECT(T9)
# 设置安装路径
SET(CMAKE_INSTALL_PREFIX "D:\\T9")
# 添加一个配置文件，用于处理CMake对源码的设置
CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

#是否使用自己的MathFunctions库
OPTION(USE_MYMATH
		"Use provide math implementation" ON)
		
#是否加入 MathFunctions库
IF(USE_MYMATH)
	INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/math")
	ADD_SUBDIRECTORY(math)
	#预声明外部lib库
	SET(EXTRA_LIBS_lib ${EXTRA_LIBS_lib} MathFunctions)
	MESSAGE(STATUS ${EXTRA_LIBS_lib})
ENDIF(USE_MYMATH)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_SRCS)


#指定生成目标
ADD_EXECUTABLE(T9 ${DIR_SRCS})
TARGET_LINK_LIBRARIES(T9 ${EXTRA_LIBS_lib})
# 安装二进制文件
INSTALL (TARGETS T9 DESTINATION bin)
# 安装源代码
#INSTALL(DIRECTORY . scripts/ DESTINATION source/
#PATTERN "obj" EXCLUDE
#PATTERN "scripts/*"
#PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
#GROUP_EXECUTE GROUP_READ)

# test 
ENABLE_TESTING()

# 测试程序是否成功运行
ADD_TEST( test_run T9 5 2)

# 测试帮助信息是否可以正常提示
add_test (test_usage T9)
set_tests_properties (test_usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

 # 测试 5 的平方
add_test (test_5_2 T9 5 2)
set_tests_properties (test_5_2
 PROPERTIES PASS_REGULAR_EXPRESSION "is 25")
# 测试 10 的 5 次方
add_test (test_10_5 T9 10 5)
set_tests_properties (test_10_5
 PROPERTIES PASS_REGULAR_EXPRESSION "is 100000")
# 测试 2 的 10 次方
add_test (test_2_10 T9 2 10)
set_tests_properties (test_2_10
 PROPERTIES PASS_REGULAR_EXPRESSION "is 1024")

 # macro
 # 定义一个宏，用来简化测试工作
macro (do_test arg1 arg2 result)
  add_test (test_${arg1}_${arg2} T9 ${arg1} ${arg2})
  set_tests_properties (test_${arg1}_${arg2}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)
 
# 使用该宏进行一系列的数据测试
do_test (5 3 "is 125")
#do_test (10 6  "is 100000")
do_test (10 6  "is 1000000")
#do_test (2 11 "is 1024")
do_test (2 11 "is 2048")


# 构建一个CPack安装包
INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_RESOURCE_FILE_LICENSE
"${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAXJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINJOR}")
INCLUDE(CPACK)


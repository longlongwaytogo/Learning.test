# CMake 最低版本要求
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(VERSION_MAXJOR 1)
SET(VERSION_MINJOR 0)



set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)


#项目信息
PROJECT(T10)
# 设置安装路径
SET(CMAKE_INSTALL_PREFIX "D:\\T10")
# 添加一个配置文件，用于处理CMake对源码的设置
CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
include_directories ("${PROJECT_BINARY_DIR}")
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
ADD_EXECUTABLE(T10 ${DIR_SRCS})
TARGET_LINK_LIBRARIES(T10 ${EXTRA_LIBS_lib})
# 安装二进制文件
INSTALL (TARGETS T10 DESTINATION bin)
# 安装源代码
#INSTALL(DIRECTORY . scripts/ DESTINATION source/
#PATTERN "obj" EXCLUDE
#PATTERN "scripts/*"
#PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
#GROUP_EXECUTE GROUP_READ)

# test 
ENABLE_TESTING()


# does the application run
#add_test (TutorialRuns T10 25)

# does the usage message work?
add_test (T8Usage T10)
set_tests_properties (T8Usage
  PROPERTIES
  PASS_REGULAR_EXPRESSION "Usage:.*number"
  )

#define a macro to simplify adding tests
macro (do_test arg result)
  add_test (TutorialComp${arg} T10 ${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endmacro ()

# do a bunch of result based tests
do_test (4 "4 is 2")
do_test (9 "9 is 3")
do_test (5 "5 is 2.236")
do_test (7 "7 is 2.645")
do_test (25 "25 is 5")
do_test (-25 "-25 is 0")
do_test (0.0001 "0.0001 is 0.01")




# 构建一个CPack安装包
INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_RESOURCE_FILE_LICENSE
"${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAXJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINJOR}")
INCLUDE(CPACK)


# CMake 常用命令整理
###1. 添加包含目录： INCLUDE_DIRECTORIES
#### 语法：
include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])  
相当于vs中的附加包含目录，例如：  

		include_directories(../../../thirdparty/comm/include)

###2.添加链接库文件目录：LINK_DIRECTORIES
#### 语法：
link_directories(directory1 directory2 ...)  
相当于vs中的附加库目录，例如：  
		
		link_directories(../../../third/lib)

###3. 查找库所在目录FIND_LIBRARY
#### 语法

		A short-hand signature is:

find_library (<VAR> name1 [path1 path2 ...])
The general signature is:

	find_library (
          <VAR>
          name | NAMES name1 [name2 ...] [NAMES_PER_DIR]
          [HINTS path1 [path2 ... ENV var]]
          [PATHS path1 [path2 ... ENV var]]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [NO_DEFAULT_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_CMAKE_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
         )  
如下：

		FIND_LIBRARY(RUNTIME_LIB rt /usr/lib  /usr/local/lib NO_DEFAULT_PATH)
cmake会在目录中查找，如果所有目录中都没有，值RUNTIME_LIB就会被赋为NO_DEFAULT_PATH

###4.添加需要的包含文件路径：target_include_directories  

target_include_directories(<target> [SYSTEM] [BEFORE]  
  <INTERFACE|PUBLIC|PRIVATE> [items1...]  
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])  

###5. 添加需要链接的库文件路径LINK_LIBRARIES
#### 语法：  
link_libraries(library1 <debug | optimized> library2 ...)  
		
		# 直接是全路径
		link_libraries(“/home/server/third/lib/libcommon.a”)
		# 下面的例子，只有库名，cmake会自动去所包含的目录搜索
		link_libraries(iconv)
		
		# 传入变量
		link_libraries(${RUNTIME_LIB})
		# 也可以链接多个
		link_libraries("/opt/MATLAB/R2012a/bin/glnxa64/libeng.so"　"/opt/MATLAB/R2012a/bin/glnxa64/libmx.so")  

###6. 设置要链接的库文件的名称TARGET_LINK_LIBRARIES   
##### 语法：
target_link_libraries(<target> [item1 [item2 [...]]]   
[[debug|optimized|general] <item>] ...)  

以下写法都可以：   

		target_link_libraries(myProject comm)       # 连接libhello.so库，默认优先链接动态库
		target_link_libraries(myProject libcomm.a)  # 显示指定链接静态库
		target_link_libraries(myProject libcomm.so) # 显示指定链接动态库

或：

		target_link_libraries(myProject libcomm.so)　　#这些库名写法都可以。
		target_link_libraries(myProject comm)
		target_link_libraries(myProject -lcomm)

###7. xxx_directories 和 target_xxx_directories 区别： 
这类命令如：  
include_directories/target_include_directories  
link_directories/ target_link_libraries   

####主要区别在于：  
- xxx\_directories 将作用于整个工程，target\_xxx\_directories 将作用于target 的项目   
- target目标文件必须已经存在（由命令add\_executable()或add\_library()所创建)，并且不能被IMPORTED修饰 
- 若使用BEFORE，则它修饰的内容会被添加到属性前面。
- 关键字INTERFACE，PUBLIC和PRIVATE指定它后面参数的作用域。PRIVATE和PUBLIC项会填充targe目标文件的INCLUDE\_DIRECTORIES属性。
- PUBLIC和INTERFACE项会填充target目标文件的INTERFACE\_INCLUDE_DIRECTORIES属性。随后的参数指定包含目录。

###8. 为工程生成库文件：
#### 语法： 
add_library(<name> <SHARED|STATIC|MODULE|UNKNOWN> IMPORTED  [GLOBAL])
例如，默认生成动态库：

	add_library(${PROJECT_NAME} MODULE ${SOURCE})

###9. 为工程生成目标文件:
#### 语法： 
add_executable(<name> [WIN32] [MACOSX_BUNDLE]  
           [EXCLUDE_FROM_ALL]  
           source1 [source2 ...])  
例如：
	
		add_executable(demo main.cpp)


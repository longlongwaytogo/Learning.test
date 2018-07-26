CMake 常用命令、变量整理：

## 一、 常用变量
- CMAKE_BINARY_DIR: CMAKE 二进制文件根路径
- CMAK_SOURCE_DIR： CMAKE 源文件根路径
- ${projectname}_SOURCE_DIR 源文件根路径
- ${projectname}_BINRRY_DIR 二进制文件根路径
- CMAKE_C_COMPILER：指定C编译器
- CMAKE_CXX_COMPILER：
- CMAKE_C_FLAGS：编译C文件时的选项，如-g；也可以通过add_definitions添加编译选项
- EXECUTABLE_OUTPUT_PATH：可执行文件的存放路径
- CMAKE_RUNTIME_OUTPUT_DIRECTORY: 输出exe路径，作用同上
- LIBRARY_OUTPUT_PATH：库文件路径
- CMAKE_LIBRARY_OUTPUT_DIRECTORY： 库文件输出路径，同上

CMAKE_BUILD_TYPE:：build 类型(Debug, Release, ...)，CMAKE_BUILD_TYPE=Debug

BUILD_SHARED_LIBS：Switch between shared and static libraries


## 二、 常用命令
- **CMake版本要求:** 
		
		CMAKE_MINIMUM_REQUIRED(VERSION 3.0)  
- **设置变量:** 

		set(var a;b;c)	：（重新设置变量值，不写${}） 
- **日志输出：**

		MESSAGE((none)|STATUS|WARNING|FATAL_ERROR   msg) 

- **添加头文件包含：**       
		
		INCLUDE_DIRECTORIES(dir1 dir2...)
		TARGET_INCLUDE_DIRECTORIES( target  dir1 dir2...)
- **添加库文件目录包含：** 

		LINK_DIRECTORIES(dir1 dir2...)
		TARGET_LINK_DIRECTORIES(target dir1 dir2...)

- **链接库文件：**  

		LINK_LIBRARIES(lib1 lib2...)  
		TARGET_LINK_LIBRARIES(target lib1 lib2...)

- **生成库文件：** 

	add_libarary([STATIC | SHARED | MODULE] [EXCLUDE_FROM_ALL]  target source)

- **生成可执行文件:** 

    add_executable(target source)

- **添加子目录：**

		add_subdirectory ：添加子目录

- **添加编译参数：**
	
		add_definitions：  
		add_definitions(-DDEBUG)将在gcc命令行添加DEBUG宏定义；

- **条件编译：**

		option(DEBUG_mode "ON for debug or OFF for release" ON) 
		IF(DEBUG_mode)
			add_definitions(-DDEBUG)
		ENDIF()

- **编译依赖设置：** 

	add_dependencies(target target_dependecy1 target_dependecy2...)

- **设置目标文件输出目录：** 
		
		SET_TARGET_PROPERTIES(ss7gw PROPERTIES                     RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")

- **查找依赖库：** 

		find_package(<package> [version] [EXACT] [QUIET] [MODULE]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [NO_POLICY_SCOPE])

		find_package(Qt5Widgets Required）


- **创建项目分组：** 

		SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
		SET_PROPERTY(TARGET project1 PROPERTY FOLDER "Core")
		SET_PROPERTY(TARGET project2 PROPERTY FOLDER "Core")

		or
		SET_TARGET_PROPERTIES(project1 PROPERTIES FOLDER "Core")
		SET_TARGET_PROPERTIES(project2 PROPERTIES FOLDER "Core")



文件结构如下：  

			Soulution
			|_Core
			|  |_project1
			|  |_project2
			|_Other

- **项目内文件分组:** 

CMake 可以通过set_property 设置visual studio 中，项目的属性，对于多个项目分类到同一目录下，可以使用：

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES FOLDER "OS")
	


## 三、常用逻辑控制：

- **if语句**


- **for语句**


- **while语句** 
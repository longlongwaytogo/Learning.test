cmake_minimum_required(VERSION 3.0)

add_executable(main main.cpp)

					 
# add_custom_command(TARGET target
					# PRE_BUILD | PRE_LINK | POST_BUILD
					# COMMAND command1 [ARGS] [args1...]
					# [COMMAND command2 [ARGS] [args2...] ...]
					# [WORKING_DIRECTORY dir]
					# [COMMENT comment] [VERBATIM])
					 
# 生成项目相关的PRE_BUILD，PRE_LINK ， POST_BUILD  处理命令
add_custom_command( TARGET main PRE_BUILD COMMAND @echo this is  test main)


# add_custom_command(OUTPUT output1 [output2 ...]
                     # COMMAND command1 [ARGS] [args1...]
                     # [COMMAND command2 [ARGS] [args2...] ...]
                     # [MAIN_DEPENDENCY depend]
                     # [DEPENDS [depends...]]
                     # [IMPLICIT_DEPENDS <lang1> depend1 ...]
                     # [WORKING_DIRECTORY dir]
                     # [COMMENT comment] [VERBATIM] [APPEND])

# 创建一个自定义输出文件
set(TEST_FILE "log.txt")
add_custom_command(OUTPUT ${TEST_FILE} COMMAND echo "this is output log.txt" COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_FILE} ${TEST_FILE} COMMENT "This is a test1")
#add_custom_command(OUTPUT ${TEST_FILE} 	COMMAND echo "Generating log.txt file..." 	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_FILE} ${TEST_FILE} COMMENT "This is a test2")

MESSAGE("cmd:${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_FILE} ${TEST_FILE}")
# 将自定义文件关联到一个Target上，这个Target不会生成任何目标
add_custom_target(Test1 ALL DEPENDS ${TEST_FILE})
 
add_custom_command( TARGET Test1 PRE_BUILD COMMAND echo "executing a fake command" COMMENT "This command will be executed before building target Test1")

#add_custom_command( TARGET Test1 PRE_BUILD COMMAND @echo this is  test)
# 作者：山庄来客 
# 来源：CSDN 
# 原文：https://blog.csdn.net/fuyajun01/article/details/8907207 
 
 
 
	
# add_custom_target(Name [ALL] [command1 [args1...]]
				# [COMMAND command2 [args2...] ...]
				# [DEPENDS depend depend depend ... ]
				# [WORKING_DIRECTORY dir]
				# [COMMENT comment] [VERBATIM]
				# [SOURCES src1 [src2...]])

# 生成独立的命令项目,cmd 依附于 项目内的 .rule 文件
add_custom_target(test  @echo this target cmd  COMMAND @echo this target cmd2 SOURCES test.cpp)

# 输出当前CMAKELIST.txt 文件完整路径
# MESSAGE("Current_LIST_FILE:${CMAKE_CURRENT_LIST_FILE}")
# 输出当前行号
# MESSAGE("CURRENT_LIST_LINE:${CMAKE_CURRENT_LIST_LINE}")


ADD_SUBDIRECTORY(gen)
set_property(SOURCE ${CMAKE_CURRENT_BINARY_DIR}/gen/test.c PROPERTY GENERATED 1)
add_executable(test_c ${CMAKE_CURRENT_BINARY_DIR}/gen/test.c)
# test_c  依赖于 gen_test_c 生成test.c 文件才能执行编译
add_dependencies(test_c gen_test_c) 

 

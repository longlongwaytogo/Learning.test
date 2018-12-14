cmake_minimum_required(VERSION 3.1)

project(hello)

# https://stackoverflow.com/questions/31966135/cmake-source-group-not-working-correctly-with-hierarchical-project-setup

file(GLOB_RECURSE LOCAL_SOURCE RELATIVE "${CMAKE_SOURCE_DIR}/source" ${CMAKE_SOURCE_DIR}/source/*.h ${CMAKE_SOURCE_DIR}/source/*.cpp)

message(${LOCAL_SOURCE})
message(----------------------)
foreach(dir  ${LOCAL_SOURCE})
message(${dir})
endforeach()
message(----------------------)
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
		#message(----${_source}----)
        if (IS_ABSOLUTE "${_source}") # 如果是绝对路径
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}") # 获取相对路径
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
		message(${_source_path_msvc}=${_source} ==${_source_path})
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

#function(my_add_executable)
#    foreach(_source IN ITEMS ${ARGN})
#        assign_source_group(${_source})
#    endforeach()
#    add_executable(${ARGV})
#endfunction(my_add_executable)

# 函数名 gen_group 
# baseDir： 基于项目生成的根目录如，include， source 
# findPath： 文件搜索目录
# files: 文件列表
FUNCTION(gen_group  baseDir findPath files)
message(--------------------------------------------)
	foreach( filename ${files})
	message(origin:${filename})
	MESSAGE(findpath:${findPath})
		file(RELATIVE_PATH relativepath ${findPath} "${filename}")	 # 获取相对路径
		get_filename_component(group_name ${relativepath} DIRECTORY)
		SET(group_name_new "${group_name}")
		string(REPLACE "/" "\\" _source_path_msvc "${group_name_new}") # 将Unix风格斜杠转换为window风格
		source_group("${baseDir}\\${_source_path_msvc}"  FILES ${filename})
		message(---"${baseDir}\\${_source_path_msvc}"  ${filename}---)
	ENDFOREACH()
EndFunction()

file(GLOB_RECURSE Local_CPP   ${CMAKE_SOURCE_DIR}/source/*.h ${CMAKE_SOURCE_DIR}/source/*.cpp )


#foreach( filename ${Local_CPP})
#message(${filename})
#file(RELATIVE_PATH relativepath "${CMAKE_CURRENT_SOURCE_DIR}/source" "${filename}")	 # 获取相对路径
#get_filename_component(group_name ${relativepath} DIRECTORY)
#SET(group_name_new "${group_name}")
#
# string(REPLACE "/" "\\" _source_path_msvc "${group_name_new}") # 将Unix风格斜杠转换为window风格
#source_group("source\\${_source_path_msvc}"  FILES ${filename})
#message(---"${_source_path_msvc}"  ${filename}---)
#ENDFOREACH()

gen_group("source1" ${CMAKE_SOURCE_DIR}/source "${Local_CPP}")


ADD_EXECUTABLE("hello" ${Local_CPP})
#my_add_executable(hello source/include/hello.h source/include/inc/in.h source/src/hello.cpp)
#my_add_executable(hello ${LOCAL_SOURCE})

#source_group( source\\include\\inc FILES source/include/inc/in.h)


# message(STATUS "current dir: ${CMAKE_CURRENT_SOURCE_DIR}")  
# file(WRITE test1.txt "Some messages to Write\n" )  
# file(APPEND test1.txt "Another message to write\n")  
# file(READ test1.txt CONTENTS LIMIT 4 OFFSET 12)  
# message(STATUS "contents of test1.txt is: \n ${CONTENTS}")  
# file(MD5 ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt HASH_CONTENTS)  
# message(STATUS "hash contents of test1.txt is: \n ${HASH_CONTENTS}")  
# file(STRINGS test1.txt PARSED_STRINGS)  
# message(STATUS "\n strings of test1.txt is: \n ${PARSED_STRINGS}")  
# file(GLOB files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/source/" "*.*")  
# message(STATUS  "files: ${files}")  
# file(MAKE_DIRECTORY dir1 dir2)  
# file(RENAME dir2 dir3)  
# file(REMOVE dir3)  
# file(REMOVE_RECURSE dir3)  
# file(RELATIVE_PATH relative_path ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)  
# message(STATUS "relative path : ${relative_path}")  
# file(TO_CMAKE_PATH "$ENV{PATH}" cmake_path)  
# message(STATUS "cmake path: ${cmake_path}")  
# file(TO_NATIVE_PATH "/usr/local/sbin;/usr/local/bin" native_path)  
# message(STATUS "native path: ${native_path}")  
# file(DOWNLOAD "http://www.baidu.com" ${CMAKE_CURRENT_SOURCE_DIR}/index.html SHOW_PROGRESS)  
# file(COPY test1.txt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dir1)  
# file(INSTALL test1.txt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dir1)  

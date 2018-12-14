project(test)
cmake_minimum_required(VERSION 2.8)
# file(download url local_filename_with_path)
FILE(DOWNLOAD https://codeload.github.com/longlongwaytogo/LearnWebGL/zip/gh-pages D:/LearnWebGL-gh-pages.zip )

option(STR_OP " this is switch " ON)

# set(SRC)  
# list(APPEND SRC a.cpp b.cpp)  
# list(APPEND SRC c.cpp d.cpp)  
  
# function(tst_arguments src_list)  
    # message("src_list = "${src_list})  
# endfunction()  
  
# message("SRC = "${SRC})  
# tst_arguments(${SRC})  


# function(tst_arguments2 src_list)  
    # message("ARGC = "${ARGC})  
    # message("ARGV = "${ARGV})  
  
    # set(INDEX 0)  
      
    # while(INDEX LESS ${ARGC})  
        # message("ARG = "${ARGV${INDEX}})  
        # math(EXPR INDEX "${INDEX} + 1")  
    # endwhile()  
# endfunction()  
  
# tst_arguments2(${SRC})  

# set(var "abc")                      # 定义一个变量var，初值为abc

# function(f1 arg)
    # set(${arg} "ABC" PARENT_SCOPE)  # ${arg} == var, 于是相当于set(var "ABC" PARENT_SCOPE)
  
# endfunction()

# message("before calling f1, var = ${var}")
# f1(var)                                     # 如果写成了f1(${var})会怎样？
# message("after calling f1, var = ${var}")
#cmd test

PROJECT(CMDTest)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)



# SET(LOG_FILE "log.txt")
# add_custom_command(OUTPUT ${LOG_FILE} COMMAND ECHO "this is a test")
# add_custom_target(TARGET cmd DEPENDS ${LOG_FILE})
# #add_custom_command(TARGET cmdtest COMMAND ECHO "test for this project" >${LOG_FILE})

set(TEST_FILE "log.txt")
add_custom_command(OUTPUT ${TEST_FILE} COMMAND echo "Generating log.txt file..." COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_FILE} ${TEST_FILE} COMMENT "This is a test")
add_custom_target(Test1 ALL DEPENDS ${TEST_FILE})

#add_custom_command(TARGET Test1 PRE_BUILD COMMAND md ok COMMENT "This command will be executed before building target Test1")

#execute_process(COMMAND dir )
#execute_process(COMMAND echo test12 OUTPUT_FILE info.log)
 execute_process(COMMAND echo abd    OUTPUT_FILE info.log)
 execute_process(COMMAND copy D:\\test.bat D:\\11.bat )
 execute_process(COMMAND echo 1223434567    )

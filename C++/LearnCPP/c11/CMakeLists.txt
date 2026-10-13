add_executable(c11 main.cpp)
set_target_properties(c11 PROPERTIES FOLDER "c11")

add_custom_target(run_c11 COMMAND c11 DEPENDS c11)
add_executable(01-auto 01-auto.cpp)

set_target_properties(01-auto PROPERTIES FOLDER "c11")

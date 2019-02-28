PROJECT(TestWin32)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


add_library(lib SHARED lib.cpp)

ADD_EXECUTABLE(App main.cpp)

target_link_libraries(App lib)
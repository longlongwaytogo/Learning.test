 cmake_minimum_required(VERSION 3.8)
project(main_PY)
add_library(main SHARED main.cpp main_wrap.cxx)
include_directories("C:\\Program Files\\Emscripten\\python\\2.7.5.3_64bit\\include")
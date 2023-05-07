# https://www.kitware.com//create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
cmake_minimum_required(VERSION 3.10)
project(cmake_auto_export VERSION 1.0.0 LANGUAGES C CXX)
 
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Release)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11")
add_definitions(-DDEBUG -DREAL_COOL_ENGINEER)





set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(BUILD_SHARED_LIBS ON)
	
add_library( comm comm.h comm.cpp)
add_executable(app main.cpp)
target_link_libraries(app comm)

##set_target_properties(comm PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
									
#target_link_options(comm PRIVATE "-Wl,--export-all-symbols")
message(${PROJECT_VERSION})
message(${cmake_auto_export_VERSION})

message(${PROJECT_VERSION_MAJOR})
message(${PROJECT_VERSION_MINOR})
message(${PROJECT_VERSION_PATCH})
message(STATUS ${PROJECT_VERSION_TWEAK})

include(CPack)
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_NAME "CMakeTemplate")
set(CPACK_SET_DESTDIR ON)
set(CPACK_INSTALL_PREFIX "./package/")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

install(TARGETS comm app
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)


option(CMAKE_TEMPLATE_ENABLE_TEST "Whether to enable unit tests" ON)
if (CMAKE_TEMPLATE_ENABLE_TEST)
message(STATUS "Unit tests enabled")
enable_testing()
endif()

add_test(NAME app COMMAND app)
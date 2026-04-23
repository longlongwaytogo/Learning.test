
set(targetName 4_DebugVulkan)

# Define include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Gather list of header and source files for compilation
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_executable(${targetName} ${CPP_FILES} ${HPP_FILES}
)

# Define project properties
set_property(TARGET ${targetName} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${targetName} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${targetName} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${targetName} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${targetName} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin)


# Define C++ version to be used for building the project
set_property(TARGET ${targetName} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${targetName} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${targetName} PRIVATE Vulkan::Vulkan)
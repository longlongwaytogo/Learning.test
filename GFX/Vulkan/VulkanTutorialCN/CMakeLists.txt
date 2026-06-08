cmake_minimum_required(VERSION 3.20)
project(VulkanTutorialCN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch GLFW
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Find Vulkan
find_package(Vulkan REQUIRED)

# Helper function for Vulkan examples
function(add_vulkan_example name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} PRIVATE glfw Vulkan::Vulkan)
    target_include_directories(${name} PRIVATE $ENV{VULKAN_SDK}/Include)
    target_compile_definitions(${name} PRIVATE
        GLFW_INCLUDE_VULKAN
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
    )
endfunction()

add_subdirectory(04)
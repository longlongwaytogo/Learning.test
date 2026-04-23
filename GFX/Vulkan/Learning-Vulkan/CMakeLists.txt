cmake_minimum_required(VERSION 3.10)
project(Learning-Vulkan)

# if(NOT DEFINED ENV{VULKAN_SDK})
#     message(STATUS "VULKAN_SDK environment variable is NOT set. Trying default path...")
#     # 尝试一个常见的默认路径
#     # set(ENV{VULKAN_SDK} "C:/VulkanSDK/1.3.275.0")
# endif()

find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Found Vulkan SDK: ${VULKAN_SDK}")
else()
    message(FATAL_ERROR "Vulkan SDK not found. Please set VULKAN_SDK environment variable.")
endif()

# Add any required preprocessor definitions here
if(WIN32)
    add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)
endif()


add_subdirectory(3_0_DeviceHandshake)

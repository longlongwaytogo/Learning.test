#pragma once
#include "Headers.h"
#include "VulkanLED.h"
class VulkanDevice
{
public:
    VulkanDevice(VkPhysicalDevice *inGPU);
    ~VulkanDevice();

    VkResult createDevice(std::vector<const char *> &layers, std::vector<const char *> &extensions);
    void destroyDevice();

    // Get the avaialbe queues exposed by the physical devices
    void getPhysicalDeviceQueuesAndProperties();

    // Query physical device to retrive queue properties
    uint32_t getGraphicsQueueHandle();

public:
    VkDevice localdevice; // Logical device
    VkPhysicalDevice* gpu;
    VkPhysicalDeviceProperties gpuProps; // Physical device attributes
    VkPhysicalDeviceMemoryProperties memoryProperties;

    // Queue
    VkQueue queue;                                         // Vulkan Queues object
    std::vector<VkQueueFamilyProperties> queueFamilyProps; // Store all queue families exposed by the physical device. attributes
    uint32_t graphicsQueueIndex;                           // Stores graphics queue index
    uint32_t graphicsQueueWithPresentIndex;                // Number of queue family exposed by device
    uint32_t queueFamilyCount;                             // Device specificc layer and extensions

    // Layer and extensions
    VulkanLayerAndExtension layerExtension;
};
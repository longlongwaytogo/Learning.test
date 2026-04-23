#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(VkPhysicalDevice *inGPU):gpu(inGPU)
{

}


VulkanDevice::~VulkanDevice()
{
}

VkResult VulkanDevice::createDevice(std::vector<const char *> &layers, std::vector<const char *> &extensions)
{
    return VK_SUCCESS;
}
void VulkanDevice::destroyDevice()
{
}

// Get the avaialbe queues exposed by the physical devices
void VulkanDevice::getPhysicalDeviceQueuesAndProperties()
{
}

// Query physical device to retrive queue properties
uint32_t VulkanDevice::getGraphicsQueueHandle()
{
    return 0;
}
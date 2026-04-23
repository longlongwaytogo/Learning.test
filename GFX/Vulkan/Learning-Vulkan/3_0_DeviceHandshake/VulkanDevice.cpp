#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(VkPhysicalDevice* inGPU) :gpu(inGPU)
{

}


VulkanDevice::~VulkanDevice()
{
}

VkResult VulkanDevice::createDevice(std::vector<const char*>& layers, std::vector<const char*>& extensions)
{
	layerExtension.appRequestedLayerNames = layers;
    layerExtension.appRequestedExtensionNames = extensions;
    
	// create the device with available queue information

	VkResult result;
	float queuePriorities[1] = { 1.0f };
	VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.pNext = nullptr;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.queueFamilyIndex = graphicsQueueIndex;
    queueCreateInfo.pQueuePriorities = queuePriorities;
    
	VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext = nullptr;
	deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.pEnabledFeatures = nullptr;
	deviceCreateInfo.ppEnabledLayerNames = nullptr;
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	deviceCreateInfo.ppEnabledExtensionNames = extensions.data();
	deviceCreateInfo.pEnabledFeatures = nullptr;

    result = vkCreateDevice(*gpu, &deviceCreateInfo, nullptr, &device);

    assert(result == VK_SUCCESS);
    assert(device != nullptr);


	return VK_SUCCESS;
}
void VulkanDevice::destroyDevice()
{
	vkDestroyDevice(device, NULL);
}

// Get the avaialbe queues exposed by the physical devices
void VulkanDevice::getPhysicalDeviceQueuesAndProperties()
{
	vkGetPhysicalDeviceQueueFamilyProperties(*gpu, &queueFamilyCount, nullptr);
	queueFamilyProps.resize(queueFamilyCount);

	vkGetPhysicalDeviceQueueFamilyProperties(*gpu, &queueFamilyCount, queueFamilyProps.data());
}

// Query physical device to retrive queue properties
uint32_t VulkanDevice::getGraphicsQueueHandle()
{
	//	1. Get the number of Queues supported by the Physical device
	//	2. Get the properties each Queue type or Queue Family
	//			There could be 4 Queue type or Queue families supported by physical device - 
	//			Graphics Queue	- VK_QUEUE_GRAPHICS_BIT 
	//			Compute Queue	- VK_QUEUE_COMPUTE_BIT
	//			DMA				- VK_QUEUE_TRANSFER_BIT
	//			Sparse memory	- VK_QUEUE_SPARSE_BINDING_BIT
	//	3. Get the index ID for the required Queue family, this ID will act like a handle index to
	bool found = false;
	// 1. Iterate number of Queues supported by the Physical device
	for (uint32_t i = 0; i < queueFamilyCount; i++)
	{
		// 2. Get the Graphics Queue type
		//		There could be 4 Queue type or Queue families supported by physical device - 
		//		Graphics Queue		- VK_QUEUE_GRAPHICS_BIT 
		//		Compute Queue		- VK_QUEUE_COMPUTE_BIT
		//		DMA/Transfer Queue	- VK_QUEUE_TRANSFER_BIT
		//		Sparse memory		- VK_QUEUE_SPARSE_BINDING_BIT
        if (queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            // 3. Get the index ID for the required Queue family, this ID will act like a handle index to
            //		the Queue family
            graphicsQueueIndex = i;
            found = true;
            break;
        }
	}
	assert(found);

    return 0;
}

 
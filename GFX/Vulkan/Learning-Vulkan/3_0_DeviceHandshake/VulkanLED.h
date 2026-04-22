#pragma once

#include "Headers.h"

strcut LayerProperties {
	VkLayerProperties properties;
	std::vector<VkExtensionProperties> extensions;
};

class VulkanLayerAndExtension{
	public:
		VulkanLayerAndExtension();
		~VulkanLayerAndExtension();
		
		std::vector<const char*> appRequestedLayerNames;
		std::vector<const char*> appRequestedExtensionNames;
		std::vector<LayerProperties> layerPropertiyList;
		
		VkResult getInstanceLayerProperties();
		VkResult getExtensionProperties(LayerProperties& layerProps, VkPhysicalDevice* gpu = NULL);
		
		VkResult getDeviceExtensionProperties(VkPhysicalDevice* gpu);
		
		
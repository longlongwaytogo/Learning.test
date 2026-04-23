#pragma once

#include "Headers.h"

struct LayerProperties
{
	VkLayerProperties properties;
	std::vector<VkExtensionProperties> extensions;
};

class VulkanLayerAndExtension
{
public:
	VulkanLayerAndExtension();
	~VulkanLayerAndExtension();

	std::vector<const char *> appRequestedLayerNames;
	std::vector<const char *> appRequestedExtensionNames;
	// Layers and corresponding extension list
	std::vector<LayerProperties> layerPropertyList;
	VkResult getInstanceLayerProperties();
	VkResult getExtensionProperties(LayerProperties &layerProps, VkPhysicalDevice *gpu = NULL);

	VkResult getDeviceExtensionProperties(VkPhysicalDevice *gpu);
};
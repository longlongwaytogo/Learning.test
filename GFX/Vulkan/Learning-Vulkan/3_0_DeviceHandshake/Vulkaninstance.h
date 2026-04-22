#pragma once

#include "VulkanLED.h"

class VulkanInstance {
public:
	VulkanInstance(){}
	~VulkanInstance(){}
	
public:
	VkInstance instance;
	VulkanLayerAndExtension layerExtension;
	
public:
	VkResult createInstance(std::vector<const char*>& layers, std::vector<const char*>& extensionNames, const char* applicationName);
	void destroyInstance();
#pragma once

#include "VulkanInstance.h"
#include "VulkanDevice.h"
#include "VulkanLED.h"

class VulkanApplication
{
private:
	VulkanApplication();
public:
	~VulkanApplication();
private:
	static std::unique_ptr<VulkanApplication> instance;
	static std::once_flag onlyOnce;
public:
	static VulkanApplication* GetInstance();
	
	void initialze();
	void prepare();
	void update();
	bool render();
	void deInitialize();
	
private:
	VkResult createVulkanInstance(std::vector<const char*>& layers, std::vector<const char*>& extensions,const char* applicationName);
	VkResult handShakeWithDevice(VkPhysicalDevice* gpu, std::vector<const char*>& layers,std::vector<const char*> extensions);
	VkResult enumeratePhysicalDevices(std::vector<VkPhysicalDevice>& gpus);
	
public:
	VulkanInstance instanceObj;
	VulkanDevice* deviceObj;
	
};
#includ "VulkanInstance.h"
VkResult VulkanInstance::createInstance(std::vector<const char*>& layers, std::vector<const char*>& extensionNames, const char* applicationName)
{
	layerExtension.appRequestedExtensionNames = extensionNames;
	layerExtension.appRequestLayerNames = layers;
	
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCT_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = applicationName;
	appInfo.applicationVersion = 1;
	appInfo.pEngineName = applicationName;
	appInfo.engineVersion = 1;
	appInfo.apiVersion = VK_MAKE_VERSION(1,0,0);
	
	VkInstanceCreateInfo instInfo = {};
	instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CRATE_INFO;
	instInfo.pNext
	
}
void VulkanInstance::destroyInstance()
{
	
	vkDestroyInstance(instance,NULL);
	
}
#include "VulkanApplication.h"

std::unique_ptr<VulkanApplication> VulkanApplication::instance;
std::once_flag VulkanApplication::onlyOnce;

extern std::vector<const char *> instanceExtensionNames;
extern std::vector<const char *> layerNames;
extern std::vector<const char *> deviceExtensionNames;

VulkanApplication::VulkanApplication() {
    // Constructor code here
    // At application start up, enumerate instance layers
	instanceObj.layerExtension.getInstanceLayerProperties();

	deviceObj = NULL;

}
VulkanApplication::~VulkanApplication()
{
    // Constructor code here
}

VulkanApplication* VulkanApplication::GetInstance()
{
    std::call_once(onlyOnce, [](){instance.reset(new VulkanApplication()); });
    return instance.get();

}


void VulkanApplication::initialze()
{

    char title[] = "Hello World vulkan!!!";
	// Create the Vulkan instance with specified layer and extension names.
	createVulkanInstance(layerNames, instanceExtensionNames, title);

	// Get the list of physical devices on the system
	std::vector<VkPhysicalDevice> gpuList;
	enumeratePhysicalDevices(gpuList);

    for(int i = 0; i < gpuList.size(); i++){
        const auto& gpu  = gpuList[i];
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(gpu, &props);
        std::cout << "\n====================\n";
        std::cout << "GPU device index: " << gpu << std::endl;
        std::cout << "vondor ID: " << props.vendorID << std::endl;
        std::cout << "device ID: " << props.deviceID << std::endl;
        std::cout << "GPU Name: " << props.deviceName << std::endl;
        std::cout << "Driver version: " << props.driverVersion << std::endl;
        std::cout << "Vulkan version: " << VK_VERSION_MAJOR(props.apiVersion) << "."
                << VK_VERSION_MINOR(props.apiVersion) << "."
                << VK_VERSION_PATCH(props.apiVersion) << std::endl;
        std::cout << "device type: " << props.deviceType << std::endl;
        std::cout << "pipelineCacheUUID: " << props.pipelineCacheUUID << std::endl;
        
        std::cout << "====================\n";
    }
	// This example use only one device which is available first.
	if (gpuList.size() > 0) {
		handShakeWithDevice(&gpuList[0], layerNames, deviceExtensionNames);
	}

}
void VulkanApplication::prepare()
{

}
void VulkanApplication::update()
{

}
bool VulkanApplication::render()
{
    return true;
}
void VulkanApplication::deInitialize()
{
    instanceObj.destroyInstance();
}
	
VkResult VulkanApplication::createVulkanInstance(std::vector<const char*>& layers, std::vector<const char*>& extensions,const char* applicationName)
{
  return instanceObj.createInstance(layers, extensions, applicationName);
}
// This function is responsible for creating the logical device.
// The process of logical device creation requires the following steps:-
// 1. Get the physical device specific layer and corresponding extensions [Optional]
// 2. Create user define VulkanDevice object
// 3. Provide the list of layer and extension that needs to enabled in this physical device
// 4. Get the physical device or GPU properties
// 5. Get the memory properties from the physical device or GPU
// 6. Query the physical device exposed queues and related properties
// 7. Get the handle of graphics queue
// 8. Create the logical device, connect it to the graphics queue.
VkResult VulkanApplication::handShakeWithDevice(VkPhysicalDevice* gpu, std::vector<const char*>& layers,std::vector<const char*> extensions)
{
    deviceObj = new VulkanDevice(gpu);
    if (!deviceObj){
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}
    // Print the devices available layer and their extension 
   	deviceObj->layerExtension.getDeviceExtensionProperties(gpu);
   

    vkGetPhysicalDeviceProperties(*gpu, &deviceObj->gpuProps);

    vkGetPhysicalDeviceMemoryProperties(*gpu, &deviceObj->memoryProperties);

    deviceObj->getPhysicalDeviceQueuesAndProperties();

    deviceObj->getGraphicsQueueHandle();

    deviceObj->createDevice(layers, extensions);


    return VkResult::VK_SUCCESS;
}
                            
VkResult VulkanApplication::enumeratePhysicalDevices(std::vector<VkPhysicalDevice>& gpus)
{
    uint32_t gpuCount = 0;
    VkResult result = vkEnumeratePhysicalDevices(instanceObj.instance, &gpuCount, nullptr);
    if (result != VK_SUCCESS) {
        return result;
    }
    std::cout << "\nNumber of physical devices found: " << gpuCount << std::endl;
    gpus.resize(gpuCount);
    result = vkEnumeratePhysicalDevices(instanceObj.instance, &gpuCount, gpus.data());
    if (result != VK_SUCCESS) {
        return result;
    }   
    return VkResult::VK_SUCCESS;
}

#include "VulkanLED.h"
#include "VulkanApplication.h"

VulkanLayerAndExtension::VulkanLayerAndExtension() {
    // Requesting validation layers and extensions for the application
    // appRequestedLayerNames.push_back("VK_LAYER_KHRONOS_validation");
    // appRequestedExtensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
}


VulkanLayerAndExtension::~VulkanLayerAndExtension() {
    // Cleanup if necessary
}

VkResult VulkanLayerAndExtension::getInstanceLayerProperties() {
    uint32_t layerCount = 0;
    VkResult result = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    if (result != VK_SUCCESS) {
        return result;
    }

    std::vector<VkLayerProperties> availableLayers(layerCount);
    result = vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    if (result != VK_SUCCESS) {
        return result;
    }

    // Store the layer properties and their extensions
    std::cout << "\nInstanced Layers" << std::endl;
	std::cout << "===================" << std::endl;
    for (const auto& layer : availableLayers) {
	    std::cout <<"\n"<< layer.description <<"\n\t|\n\t|---[Layer Name]--> " << layer.layerName <<"\n";
        LayerProperties layerProps;
        layerProps.properties = layer;

        // Get the extensions for this layer
        uint32_t extensionCount = 0;
        result = vkEnumerateInstanceExtensionProperties(layer.layerName, &extensionCount, nullptr);
        if (result != VK_SUCCESS) {
            return result;
        }

        layerProps.extensions.resize(extensionCount);
        result = vkEnumerateInstanceExtensionProperties(layer.layerName, &extensionCount, layerProps.extensions.data());
        if (result != VK_SUCCESS) {
            return result;
        }

        layerPropertyList.push_back(layerProps);
        // Print extension name for each instance layer
		for (auto j : layerProps.extensions) {
			std::cout << "\t\t|\n\t\t|---[Layer Extension]--> " << j.extensionName << "\n";
		}
    }

    return VK_SUCCESS;
}


VkResult VulkanLayerAndExtension::getExtensionProperties(LayerProperties& layerProps, VkPhysicalDevice* gpu)
{
    return VK_SUCCESS;
}
		
VkResult VulkanLayerAndExtension::getDeviceExtensionProperties(VkPhysicalDevice* gpu)
{
    VkResult result = VK_SUCCESS;
    uint32_t extensionCount = 0;
    result = vkEnumerateDeviceExtensionProperties(*gpu, nullptr, &extensionCount, nullptr);

    if (result != VK_SUCCESS) {
        return result;
    }
    std::cout << "\nDevice Extensions" << std::endl;
    std::cout << "===================" << std::endl;
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    result = vkEnumerateDeviceExtensionProperties(*gpu, nullptr, &extensionCount, availableExtensions.data());
    if (result != VK_SUCCESS) {
        return result;
    }

    for(const auto& ext : availableExtensions) {
        std::cout << "\t|--- " << ext.extensionName << "\n";
    }

    VulkanApplication* appObj = VulkanApplication::GetInstance();
	std::vector<LayerProperties>* instanceLayerProp = &appObj->GetInstance()->instanceObj.layerExtension.layerPropertyList;
	for (auto globalLayerProp : *instanceLayerProp) {
		LayerProperties layerProps;
		layerProps.properties = globalLayerProp.properties;

		if (result = getExtensionProperties(layerProps, gpu))
			continue;

		std::cout << "\n" << globalLayerProp.properties.description << "\n\t|\n\t|---[Layer Name]--> " << globalLayerProp.properties.layerName << "\n";
		layerPropertyList.push_back(layerProps);

		if (layerProps.extensions.size()) {
			for (auto j : layerProps.extensions) {
				std::cout << "\t\t|\n\t\t|---[Device Extesion]--> " << j.extensionName << "\n";
			}
		}
		else {
			std::cout << "\t\t|\n\t\t|---[Device Extesion]--> No extension found \n";
		}
	}

    return VK_SUCCESS;
}
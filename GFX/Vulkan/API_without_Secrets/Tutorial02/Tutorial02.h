#if !defined(TUTORIAL02_HEADER)
#define TUTORIAL02_HEADER

#include <vector>
#include "vulkan.h"
#include "OperatingSystem.h"

namespace ApiWithoutSecrets {
	
  // ************************************************************ //
  // VulkanTutorial02Parameters                                   //
  //                                                              //
  // Vulkan specific parameters                                   //
  // ************************************************************ //
  
  struct VulkanTutorial02Parameters {
	  VkInstance					Instance;
	  VkPhysicalDevice				PhysicalDevice;
	  VkDevice						Device;
	  VkQueue						GraphicsQueue;
	  VkQueue						PresentQueue;
	  uint32_t						GraphicsQueueFamilyIndex;
	  uint32_t						PresentQueueFamilyIndex;
	  VkSurfaceKHR					PresentationSurface;
	  VkSwapchainKHR				SwapChain;
	  std::vector<VkCommandBuffer>  PresentQueueCmdBuffers;
	  VkCommandPool					PresentQueueCmdPool;
	  VkSemaphore					ImageAvailableSemaphore;
	  VkSemaphore                   RenderingFinishedSemaphore;

	  VulkanTutorial02Parameters() :
	  Instance(VK_NULL_HANDLE),
	  PhysicalDevice(VK_NULL_HANDLE),
	  Device(VK_NULL_HANDLE),
	  GraphicsQueue(VK_NULL_HANDLE),
	  PresentQueue(VK_NULL_HANDLE),
	  GraphicsQueueFamilyIndex(0),
	  PresentQueueFamilyIndex(0),
	  PresentationSurface(VK_NULL_HANDLE),
	  SwapChain(VK_NULL_HANDLE),
	  PresentQueueCmdBuffers(0),
	  PresentQueueCmdPool(VK_NULL_HANDLE) {}
	  
  };


  // ************************************************************ //
  // Tutorial02                                                   //
  //                                                              //
  // Class for presenting Vulkan usage topics                     //
  // ************************************************************ //
  
  class Tutorial02 : public OS::TutorialBase {
  public:
	Tutorial02();
	~Tutorial02();
	
	bool PrepareVulkan( OS::WindowParameters parameters );
	bool CreateSwapChain();
	bool OnWindowSizeChanged() override;
	bool CreateCommandBuffers();
	bool Draw() override;
  private:
  
	OS::LibraryHandle			VulkanLibrary;
	OS::WindowParameters		Window;
	VulkanTutorial02Parameters  Vulkan;
	
	bool						LoadVulkanLibrary();
	bool						LoadExportedEntryPoints();
	bool						LoadGlobalLevelEntryPoints();
	bool						CreateInstance();
	bool						LoadInstanceLevelEntryPoints();
	bool						CreatePresentationSurface();
	bool						CreateDevice();
	bool						CheckPhysicalDeviceProperties(VkPhysicalDevice physical_device,uint32_t &graphics_queue_family_index,uint32_t &present_queue_family_index);
	bool 						LoadDeviceLevelEntryPoints();
	bool						GetDeviceQueue();
	bool						CreateSemaphores();
	bool						RecordCommandBuffers();
	void						Clear();
	
	bool						CheckExtensionAvailability( const char* extension_name,const std::vector<VkExtensionProperties> & available_extensions);
	uint32_t					GetSwapChainNumImages( VkSurfaceCapabilitiesKHR &surface_capabilities );
	VkSurfaceFormatKHR			GetSwapChainFormat( std::vector<VkSurfaceFormatKHR> &surface_formats );
	VkExtent2D					GetSwapChainExtent( VkSurfaceCapabilitiesKHR & surface_capabilities );
	VkImageUsageFlags			GetSwapChainUsageFlags(VkSurfaceCapabilitiesKHR &surface_capabilities );
	VkSurfaceTransformFlagBitsKHR GetSwapChainTransform( VkSurfaceCapabilitiesKHR &surface_capabilities);
	VkPresentModeKHR			GetSwapChainPresentMode( std::vector<VkPresentModeKHR> &present_modes );
  
		
  };
  
} // namespace ApiWithoutSecrets


#endif 
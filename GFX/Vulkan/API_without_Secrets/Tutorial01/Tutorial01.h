// Tutorial01.h

#if !defined(TUTORIAL_01_HEADER)
#define TUTORIAL_01_HEADER

#include "vulkan.h"
#include "OperatingSystem.h"

namespace ApiWithoutSecrets {
	
	
  // ************************************************************ //
  // VulkanTutorial01Parameters                                   //
  //                                                              //
  // Vulkan specific parameters                                   //
  // ************************************************************ //
	
	struct VulkanTutorial01Parameters {
		VkInstance Instance;
		VkDevice Device;
		uint32_t QueueFamilyIndex;
		VkQueue  Queue;
		
		
		VulkanTutorial01Parameters():
		Instance(VK_NULL_HANDLE),
		Device(VK_NULL_HANDLE),
		QueueFamilyIndex(0),
		Queue(VK_NULL_HANDLE) {}
	};
	
	
  // ************************************************************ //
  // Tutorial01                                                   //
  //                                                              //
  // Class for presenting Vulkan usage topics                     //
  // ************************************************************ //
	
	class Tutorial01 : public OS::TutorialBase {
	public:
		Tutorial01();
		~Tutorial01();
		
		bool OnWindowSizeChanged() override;
		bool Draw() override;
		
		bool PrepareVulkan();
		
	private:
		OS::LibraryHandle		VulkanLibrary;
		VulkanTutorial01Parameters Vulkan;
		
		bool LoadVulkanLibrary();
		bool LoadExportedEntryPoints();
		bool LoadGlobalLevelEntryPoints();
		bool CreateInstance();
		bool LoadInstanceLevelEntryPoints();
		bool CreateDevice();
		bool CheckPhysicalDeviceProperties(VkPhysicalDevice physical_device, uint32_t &queue_family_index);
		bool LoadDeviceLevelEntryPoints();
		bool GetDeviceQueue();
	};
	
	
	
}
#endif // TUTORIAL_01_HEADER
#if !defined(TUTORIAL03_HEADER)
#define TUTORIAL03_HEADER

#include "VulkanCommon.h"
#include "Tools.h"

namespace ApiWithoutSecrets {
	
  // ************************************************************ //
  // VulkanTutorial03Parameters                                   //
  //                                                              //
  // Vulkan specific parameters                                   //
  // ************************************************************ //
  
  struct VulkanTutorial03Parameters {
	 VkRenderPass 						RenderPass;
	 std::vector<VkFramebuffer>			Framebuffers;
	 VkPipeline							GraphicsPipeline;
	 VkSemaphore						ImageAvailableSemaphore;
	 VkSemaphore						RenderingFinishedSemaphore;
	 VkCommandPool						GraphicsCommandPool;
	 std::vector<VkCommandBuffer>		GraphicsCommandBuffers;
	 
	 
    VulkanTutorial03Parameters() :
      RenderPass( VK_NULL_HANDLE ),
      Framebuffers(),
      GraphicsCommandPool( VK_NULL_HANDLE ),
      GraphicsCommandBuffers(),
      GraphicsPipeline( VK_NULL_HANDLE ),
      ImageAvailableSemaphore( VK_NULL_HANDLE ),
      RenderingFinishedSemaphore( VK_NULL_HANDLE ) {
    }
  };


  // ************************************************************ //
  // Tutorial03                                                   //
  //                                                              //
  // Class for presenting Vulkan usage topics                     //
  // ************************************************************ //
  
  class Tutorial03 : public VulkanCommon {
  public:
	Tutorial03();
	~Tutorial03();
	
	bool CreateRenderPass();
	bool CreateFramebuffers();
	bool CreatePipeline();
	bool CreateSemaphores();
	bool CreateCommandBuffers();
	bool RecordCommandBuffers();
	
	bool Draw() override;
	
  private:
	VulkanTutorial03Parameters Vulkan;	

    Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>     CreateShaderModule( const char* filename );
    Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout> CreatePipelineLayout();
    bool                                                              CreateCommandPool( uint32_t queue_family_index, VkCommandPool *pool );
    bool                                                              AllocateCommandBuffers( VkCommandPool pool, uint32_t count, VkCommandBuffer *command_buffers );

    void                                                              ChildClear() override;
    bool                                                              ChildOnWindowSizeChanged() override;
  };
  
} // namespace ApiWithoutSecrets

#endif // TUTORIAL_03_HEADER
// Tutorial02.cpp

#include "Tutorial03.h"
#include "VulkanFunctions.h"


namespace ApiWithoutSecrets {


	Tutorial03::Tutorial03() :
		Vulkan() {
	}

	bool Tutorial03::CreateRenderPass() {
		VkAttachmentDescription attachment_descriptions[] = {
			{	0,
				GetSwapChain().Format,
				VK_SAMPLE_COUNT_1_BIT,
				VK_ATTACHMENT_LOAD_OP_CLEAR,
				VK_ATTACHMENT_STORE_OP_STORE,
				VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				VK_ATTACHMENT_STORE_OP_DONT_CARE,
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
			}
		};

		VkAttachmentReference color_attachment_references[] = {
			{
			   0,
			   VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
			}
		};

		VkSubpassDescription subpass_descriptions[] = {
		  {
			0,                                          // VkSubpassDescriptionFlags      flags
			VK_PIPELINE_BIND_POINT_GRAPHICS,            // VkPipelineBindPoint            pipelineBindPoint
			0,                                          // uint32_t                       inputAttachmentCount
			nullptr,                                    // const VkAttachmentReference   *pInputAttachments
			1,                                          // uint32_t                       colorAttachmentCount
			color_attachment_references,                // const VkAttachmentReference   *pColorAttachments
			nullptr,                                    // const VkAttachmentReference   *pResolveAttachments
			nullptr,                                    // const VkAttachmentReference   *pDepthStencilAttachment
			0,                                          // uint32_t                       preserveAttachmentCount
			nullptr                                     // const uint32_t*                pPreserveAttachments
		  }
		};

		VkRenderPassCreateInfo render_pass_create_info = {
		  VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,    // VkStructureType                sType
		  nullptr,                                      // const void                    *pNext
		  0,                                            // VkRenderPassCreateFlags        flags
		  1,                                            // uint32_t                       attachmentCount
		  attachment_descriptions,                      // const VkAttachmentDescription *pAttachments
		  1,                                            // uint32_t                       subpassCount
		  subpass_descriptions,                         // const VkSubpassDescription    *pSubpasses
		  0,                                            // uint32_t                       dependencyCount
		  nullptr                                       // const VkSubpassDependency     *pDependencies
		};
		if (vkCreateRenderPass(GetDevice(), &render_pass_create_info, nullptr, &Vulkan.RenderPass) != VK_SUCCESS) {
			std::cout << "Could not create render pass!" << std::endl;
			return false;
		}

		return true;
	}


	bool Tutorial03::CreateFramebuffers() {
		const std::vector<ImageParameters> &swap_chain_images = GetSwapChain().Images;
		Vulkan.Framebuffers.resize(swap_chain_images.size());

		for (size_t i = 0; i < swap_chain_images.size(); ++i) {
			VkFramebufferCreateInfo framebuffer_create_info = {
				VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,  // VkStructureType                sType
				nullptr,                                    // const void                    *pNext
				0,                                          // VkFramebufferCreateFlags       flags
				Vulkan.RenderPass,                          // VkRenderPass                   renderPass
				1,                                          // uint32_t                       attachmentCount
				&swap_chain_images[i].View,                 // const VkImageView             *pAttachments
				300,                                        // uint32_t                       width
				300,                                        // uint32_t                       height
				1                                           // uint32_t                       layers
			};

			if (vkCreateFramebuffer(GetDevice(), &framebuffer_create_info, nullptr, &Vulkan.Framebuffers[i]) != VK_SUCCESS) {
				std::cout << "Could not create a framebuffer!" << std::endl;
				return false;
			}
		}
		return true;
	}


	Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule> Tutorial03::CreateShaderModule(const char* filename) {
		const std::vector<char> code = Tools::GetBinaryFileContents(filename);
		if (code.size() == 0) {
			return Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>();
		}

		VkShaderModuleCreateInfo shader_module_create_info = {
			VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,    // VkStructureType                sType
			nullptr,                                        // const void                    *pNext
			0,                                              // VkShaderModuleCreateFlags      flags
			code.size(),                                    // size_t                         codeSize
			reinterpret_cast<const uint32_t*>(&code[0])     // const uint32_t                *pCode
		};

		VkShaderModule shader_module;
		if (vkCreateShaderModule(GetDevice(), &shader_module_create_info, nullptr, &shader_module) != VK_SUCCESS) {
			std::cout << "Could not create shader module from a \"" << filename << "\" file!" << std::endl;
			return Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>();
		}

		return Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>(shader_module, vkDestroyShaderModule, GetDevice());
	}

	Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout> Tutorial03::CreatePipelineLayout() {
		VkPipelineLayoutCreateInfo layout_create_info = {
			VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, // sType
			nullptr,										// pNext
			0,											    // flags
			0,												// setLayoutCount
			nullptr,										// vkDescriptorSetlayout
			0,												// pushConstantRangeCount
			nullptr
		};

		VkPipelineLayout pipeline_layout;
		if (vkCreatePipelineLayout(GetDevice(), &layout_create_info, nullptr, &pipeline_layout) != VK_SUCCESS) {
			std::cout << "Could not create pipeline layout!" << std::endl;
			return Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout>();
		}
		return Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout>(pipeline_layout, vkDestroyPipelineLayout, GetDevice());

	}

	bool Tutorial03::CreatePipeline() {
		Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule> vertex_shader_module = CreateShaderModule("Data03/vert.spv");
		Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule> fragment_shader_module = CreateShaderModule("Data03/frag.spv");

		if (!vertex_shader_module || !fragment_shader_module) {
			return false;
		}

		std::vector<VkPipelineShaderStageCreateInfo> shader_stage_create_infos = {
			// vertex shader
			{
				VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, //sType
				nullptr,		//*pNext
				0, // flags
				VK_SHADER_STAGE_VERTEX_BIT, // stage
				vertex_shader_module.Get(),	  // VkShaderModule
				"main",							// pName
				nullptr		// pSecializationInfo
			},
			// fragment shader
			{
				VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
				nullptr,
				0,
				VK_SHADER_STAGE_FRAGMENT_BIT,
				fragment_shader_module.Get(),
				"main",
				nullptr
			}
		};

		VkPipelineVertexInputStateCreateInfo vertex_input_state_create_info = {
			VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
			nullptr,
			0,
			0,  // vertexBindingDescriptionCount
			nullptr, //pVertexBindingDescriptions
			0, // vertexAttrbuteDescriptionCount
			nullptr
		};

		VkPipelineInputAssemblyStateCreateInfo input_assembly_state_create_info = {
			VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
			nullptr,
			0,
			VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			VK_FALSE  // primitiveRestartEnable
		};

		VkViewport viewport = {
			0.0f,  // x
			0.0f,  // y
			300.0f, // width
			300.0f, // height
			0.0f,  // minDepth
			1.0f // maxDepth
		};
	

		VkRect2D scissor = {   // VKoffset2D offset
			{
				0,   // x 
				0   // y
			},
			{
				300,
				300
			}
		};

    VkPipelineViewportStateCreateInfo viewport_state_create_info = {
      VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,        // VkStructureType                                sType
      nullptr,                                                      // const void                                    *pNext
      0,                                                            // VkPipelineViewportStateCreateFlags             flags
      1,                                                            // uint32_t                                       viewportCount
      &viewport,                                                    // const VkViewport                              *pViewports
      1,                                                            // uint32_t                                       scissorCount
      &scissor                                                      // const VkRect2D                                *pScissors
    };
		VkPipelineRasterizationStateCreateInfo rasterization_state_create_info = {
			VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
			nullptr,
			0,				// VkPipelineRasterizationStateCreateFlags Flags
			VK_FALSE,		// depthClampEnable
			VK_FALSE,		// rasterizerDiscardEnable
			VK_POLYGON_MODE_FILL, // vkPolygonMode 
			VK_CULL_MODE_BACK_BIT, // vkCullmodeFlags
			VK_FRONT_FACE_COUNTER_CLOCKWISE,  // vkFrontFace
			VK_FALSE,			// depthBiasEnable
			0.0f,				// depthBiasConstantFactor
			0.0f,				// depthBiasClamp
			0.0f,				// depthBiasSlopeFactor
			1.0f				// lineWidth

		};

		VkPipelineMultisampleStateCreateInfo multisample_state_create_info = {
			VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
			nullptr,
			0,
			VK_SAMPLE_COUNT_1_BIT,		// vkSampleCountFlagBits RasterizationSamples
			VK_FALSE,					// sampleShadingEnable
			1.0f,						// float minSampleShading
			nullptr,					// VkSamplemask 
			VK_FALSE,					// alpahToCoverageEnable
			VK_FALSE					// alphaToOneEnable
		};

		VkPipelineColorBlendAttachmentState color_blend_attachment_state = {
			VK_FALSE,					// blendEnable
			VK_BLEND_FACTOR_ONE,		// srcColorBlendFactor
			VK_BLEND_FACTOR_ZERO,       // destColorBlendFactor
			VK_BLEND_OP_ADD,			// colorBlendOp
			VK_BLEND_FACTOR_ONE,		// srcAlphaBlendFactor
			VK_BLEND_FACTOR_ZERO,		// dstAlpaBlendFactor
			VK_BLEND_OP_ADD,			// alpahBlendOp
			VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
		};

		VkPipelineColorBlendStateCreateInfo color_blend_state_create_info = {
			VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
			nullptr,			// pnext
			0,					// VkpipelineColorBlendStateCreateFlags
			VK_FALSE,			// logicOpEnable
			VK_LOGIC_OP_COPY,	// logicOp
			1,					// attachmentCount
			&color_blend_attachment_state, // VkPipelineColorBlendAttachmentState 
			{0.0f,0.0f,0.0f,0.0f}		// blendConstants[4]
		};

		Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout> pipeline_layout = CreatePipelineLayout();
		if (!pipeline_layout) {
			return false;
		}

		VkGraphicsPipelineCreateInfo pipeline_create_info = {
			VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
			nullptr,
			0,							// VkPipelineCreateFlags
			static_cast<uint32_t>(shader_stage_create_infos.size()), // stageCount
			&shader_stage_create_infos[0],
			&vertex_input_state_create_info,
			&input_assembly_state_create_info,
			nullptr,
			&viewport_state_create_info,
			&rasterization_state_create_info,
			&multisample_state_create_info,
			nullptr,	// VkPipelineDepthStencilStateCreateInofo;
			&color_blend_state_create_info,		// VkPipelineColorBlendStateCreateInfo
			nullptr,							// VkPipelineDynamicStateCreateInfo
			pipeline_layout.Get(),				//VkPipelinelayout
			Vulkan.RenderPass,					// RenderPass
			0,
			VK_NULL_HANDLE,			// basePipelineHandle
			-1						// basePipelineIndex
		};

		if (vkCreateGraphicsPipelines(GetDevice(), VK_NULL_HANDLE, 1, &pipeline_create_info, nullptr, &Vulkan.GraphicsPipeline) != VK_SUCCESS) {
			std::cout << "Could not create graphics pipeline!" << std::endl;
			return false;
		}
		return true;
	}

	bool Tutorial03::CreateSemaphores() {
		VkSemaphoreCreateInfo semaphore_create_info = {
			VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,      // VkStructureType          sType
			nullptr,                                      // const void*              pNext
			0                                             // VkSemaphoreCreateFlags   flags
		};

		if ((vkCreateSemaphore(GetDevice(), &semaphore_create_info, nullptr, &Vulkan.ImageAvailableSemaphore) != VK_SUCCESS) ||
			(vkCreateSemaphore(GetDevice(), &semaphore_create_info, nullptr, &Vulkan.RenderingFinishedSemaphore) != VK_SUCCESS)) {
			std::cout << "Could not create semaphores!" << std::endl;
			return false;
		}

		return true;
	}

	bool Tutorial03::CreateCommandBuffers() {
		if (!CreateCommandPool(GetGraphicsQueue().FamilyIndex, &Vulkan.GraphicsCommandPool)) {
			std::cout << "Could not create command pool!" << std::endl;
			return false;
		}
    uint32_t image_count = static_cast<uint32_t>(GetSwapChain().Images.size());
    Vulkan.GraphicsCommandBuffers.resize( image_count, VK_NULL_HANDLE );

    if( !AllocateCommandBuffers( Vulkan.GraphicsCommandPool, image_count, &Vulkan.GraphicsCommandBuffers[0] ) ) {
      std::cout << "Could not allocate command buffers!" << std::endl;
      return false;
    }
    return true;
  }

  bool Tutorial03::CreateCommandPool( uint32_t queue_family_index, VkCommandPool *pool ) {
    VkCommandPoolCreateInfo cmd_pool_create_info = {
      VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,     // VkStructureType                sType
      nullptr,                                        // const void                    *pNext
      0,                                              // VkCommandPoolCreateFlags       flags
      queue_family_index                              // uint32_t                       queueFamilyIndex
    };

		if (vkCreateCommandPool(GetDevice(), &cmd_pool_create_info, nullptr, pool) != VK_SUCCESS) {
			return false;
		}
		return true;
	}

	bool Tutorial03::AllocateCommandBuffers(VkCommandPool pool, uint32_t count, VkCommandBuffer* command_buffers) {
		VkCommandBufferAllocateInfo command_buffer_allocate_info = {
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			nullptr,
			pool,
			VK_COMMAND_BUFFER_LEVEL_PRIMARY,  // level
			count
		};
		if (vkAllocateCommandBuffers(GetDevice(), &command_buffer_allocate_info, command_buffers) != VK_SUCCESS) {
			return false;
		}
		return true;
	}


	bool Tutorial03::RecordCommandBuffers() {

		VkCommandBufferBeginInfo graphics_command_buffer_begin_info = {
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			nullptr,
			VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
			nullptr
		};

		VkImageSubresourceRange image_subresource_range = {
			VK_IMAGE_ASPECT_COLOR_BIT,                      // VkImageAspectFlags             aspectMask
			0,                                              // uint32_t                       baseMipLevel
			1,                                              // uint32_t                       levelCount
			0,                                              // uint32_t                       baseArrayLayer
			1                                               // uint32_t                       layerCount
		};

		VkClearValue clear_value = {
			{ 1.0f, 0.8f, 0.4f, 0.0f },                     // VkClearColorValue              color
		};
		const std::vector<ImageParameters>& swap_chain_images = GetSwapChain().Images;

		for(size_t i = 0; i < Vulkan.GraphicsCommandBuffers.size(); ++i) {
			vkBeginCommandBuffer(Vulkan.GraphicsCommandBuffers[i], &graphics_command_buffer_begin_info);

			if (GetPresentQueue().Handle != GetGraphicsQueue().Handle) {
				VkImageMemoryBarrier barrier_from_present_to_draw = {
					VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					nullptr,
					VK_ACCESS_MEMORY_READ_BIT, // srcAccessMask
					VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, // dstAccessmask
					VK_IMAGE_LAYOUT_UNDEFINED,			// oldLayout
					VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,		// newLayout
					GetPresentQueue().FamilyIndex,
					GetGraphicsQueue().FamilyIndex,
					swap_chain_images[i].Handle,
					image_subresource_range };
				vkCmdPipelineBarrier(Vulkan.GraphicsCommandBuffers[i], VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
					VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier_from_present_to_draw);
			}

			VkRenderPassBeginInfo render_pass_begin_info = {
				VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
				nullptr,
				Vulkan.RenderPass,
				Vulkan.Framebuffers[i],
				{
					{ 0,
					  0
					 },
					 { 300,
					   300,
					}
				},
				1,
				&clear_value
			};
			vkCmdBeginRenderPass(Vulkan.GraphicsCommandBuffers[i], &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(Vulkan.GraphicsCommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, Vulkan.GraphicsPipeline);
			vkCmdDraw(Vulkan.GraphicsCommandBuffers[i], 3, 1, 0, 0);
			vkCmdEndRenderPass(Vulkan.GraphicsCommandBuffers[i]);
			if (GetGraphicsQueue().Handle != GetPresentQueue().Handle) {
				VkImageMemoryBarrier barrier_from_draw_to_present = {
					VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,       // VkStructureType              sType
					nullptr,                                      // const void                  *pNext
					VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,         // VkAccessFlags                srcAccessMask
					VK_ACCESS_MEMORY_READ_BIT,                    // VkAccessFlags                dstAccessMask
					VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,              // VkImageLayout                oldLayout
					VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,              // VkImageLayout                newLayout
					GetGraphicsQueue().FamilyIndex,               // uint32_t                     srcQueueFamilyIndex
					GetPresentQueue().FamilyIndex,                // uint32_t                     dstQueueFamilyIndex
					swap_chain_images[i].Handle,                  // VkImage                      image
					image_subresource_range                       // VkImageSubresourceRange      subresourceRange
				};
				vkCmdPipelineBarrier(Vulkan.GraphicsCommandBuffers[i], VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier_from_draw_to_present);
			}
			if (vkEndCommandBuffer(Vulkan.GraphicsCommandBuffers[i]) != VK_SUCCESS) {
				std::cout << "Could not record command buffer!" << std::endl;
				return false;
			}
		}
		return true;
	}

	bool Tutorial03::ChildOnWindowSizeChanged() {
		if (!CreateRenderPass()) {
			return false;
		}
		if (!CreateFramebuffers()) {
			return false;
		}
		if (!CreatePipeline()) {
			return false;
		}
		if (!CreateCommandBuffers()) {
			return false;
		}
		if (!RecordCommandBuffers()) {
			return false;
		}

		return true;
	}


	bool Tutorial03::Draw() {
		VkSwapchainKHR swap_chain = GetSwapChain().Handle;
		uint32_t image_index;
		VkResult result = vkAcquireNextImageKHR(GetDevice(), swap_chain, UINT64_MAX, Vulkan.ImageAvailableSemaphore, VK_NULL_HANDLE, &image_index);
		switch(result) {
		case VK_SUCCESS:
		case VK_SUBOPTIMAL_KHR:
			break;
		case VK_ERROR_OUT_OF_DATE_KHR:
			return OnWindowSizeChanged();
		default:
			std::cout << "Problem occurred during swap chain image acquisition!" << std::endl;
			return false;
		}

		VkPipelineStageFlags wait_dst_stage_mask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		VkSubmitInfo submit_info = {
			VK_STRUCTURE_TYPE_SUBMIT_INFO,                // VkStructureType              sType
			nullptr,                                      // const void                  *pNext
			1,                                            // uint32_t                     waitSemaphoreCount
			&Vulkan.ImageAvailableSemaphore,              // const VkSemaphore           *pWaitSemaphores
			&wait_dst_stage_mask,                         // const VkPipelineStageFlags  *pWaitDstStageMask;
			1,                                            // uint32_t                     commandBufferCount
			&Vulkan.GraphicsCommandBuffers[image_index],  // const VkCommandBuffer       *pCommandBuffers
			1,                                            // uint32_t                     signalSemaphoreCount
			&Vulkan.RenderingFinishedSemaphore            // const VkSemaphore           *pSignalSemaphores
		};

		if (vkQueueSubmit(GetGraphicsQueue().Handle, 1, &submit_info, VK_NULL_HANDLE) != VK_SUCCESS) {
			return false;
		}

		VkPresentInfoKHR present_info = {
			VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,           // VkStructureType              sType
			nullptr,                                      // const void                  *pNext
			1,                                            // uint32_t                     waitSemaphoreCount
			&Vulkan.RenderingFinishedSemaphore,           // const VkSemaphore           *pWaitSemaphores
			1,                                            // uint32_t                     swapchainCount
			&swap_chain,                                  // const VkSwapchainKHR        *pSwapchains
			&image_index,                                 // const uint32_t              *pImageIndices
			nullptr                                       // VkResult                    *pResults
		};
		result = vkQueuePresentKHR(GetPresentQueue().Handle, &present_info);

		switch (result) {
		case VK_SUCCESS:
			break;
		case VK_ERROR_OUT_OF_DATE_KHR:
		case VK_SUBOPTIMAL_KHR:
			return OnWindowSizeChanged();
		default:
			std::cout << "Problem occurred during image presentation!" << std::endl;
			return false;
		}

		return true;
	}
	void Tutorial03::ChildClear() {
		if (GetDevice() != VK_NULL_HANDLE) {
			vkDeviceWaitIdle(GetDevice());

			if ((Vulkan.GraphicsCommandBuffers.size() > 0) && (Vulkan.GraphicsCommandBuffers[0] != VK_NULL_HANDLE)) {
				vkFreeCommandBuffers(GetDevice(), Vulkan.GraphicsCommandPool, static_cast<uint32_t>(Vulkan.GraphicsCommandBuffers.size()), &Vulkan.GraphicsCommandBuffers[0]);
				Vulkan.GraphicsCommandBuffers.clear();
			}

			if (Vulkan.GraphicsCommandPool != VK_NULL_HANDLE) {
				vkDestroyCommandPool(GetDevice(), Vulkan.GraphicsCommandPool, nullptr);
				Vulkan.GraphicsCommandPool = VK_NULL_HANDLE;
			}

			if (Vulkan.GraphicsPipeline != VK_NULL_HANDLE) {
				vkDestroyPipeline(GetDevice(), Vulkan.GraphicsPipeline, nullptr);
				Vulkan.GraphicsPipeline = VK_NULL_HANDLE;
			}

			if (Vulkan.RenderPass != VK_NULL_HANDLE) {
				vkDestroyRenderPass(GetDevice(), Vulkan.RenderPass, nullptr);
				Vulkan.RenderPass = VK_NULL_HANDLE;
			}

			for (size_t i = 0; i < Vulkan.Framebuffers.size(); ++i) {
				if (Vulkan.Framebuffers[i] != VK_NULL_HANDLE) {
					vkDestroyFramebuffer(GetDevice(), Vulkan.Framebuffers[i], nullptr);
					Vulkan.Framebuffers[i] = VK_NULL_HANDLE;
				}
			}
			Vulkan.Framebuffers.clear();
		}
	}

	Tutorial03::~Tutorial03() {
		ChildClear();

		if (GetDevice() != VK_NULL_HANDLE) {
			vkDeviceWaitIdle(GetDevice());

			if (Vulkan.ImageAvailableSemaphore != VK_NULL_HANDLE) {
				vkDestroySemaphore(GetDevice(), Vulkan.ImageAvailableSemaphore, nullptr);
			}

			if (Vulkan.RenderingFinishedSemaphore != VK_NULL_HANDLE) {
				vkDestroySemaphore(GetDevice(), Vulkan.RenderingFinishedSemaphore, nullptr);
			}
		}
	}
}// ApiWithoutSecrets

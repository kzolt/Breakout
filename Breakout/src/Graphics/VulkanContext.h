#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#ifdef _DEBUG
#define ENABLE_VALIDATION_LAYERS
#endif

namespace Breakout {

	class VulkanContext
	{
	public:
		VulkanContext();
		~VulkanContext();

	private:
		bool CheckValidationLayers(const std::vector<VkLayerProperties>& layers);
		
		void SetupDebugger();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	private:
		VkInstance m_Instance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;

		std::vector<const char*> m_Extensions;
		std::vector<const char*> m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

	};

}
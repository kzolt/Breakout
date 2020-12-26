#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#ifdef _DEBUG
#define ENABLE_VALIDATION_LAYERS
#endif

namespace Breakout {

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> GraphicsFamily;

		inline bool isComplete() { return GraphicsFamily.has_value(); }
	};

	class VulkanContext
	{
	public:
		VulkanContext(Window* window);
		~VulkanContext();

	private:
		bool CheckValidationLayers(const std::vector<VkLayerProperties>& layers);
		
		void SetupDebugger();
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

		void CreateDevice();

	private:
		VkInstance m_Instance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;

		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_Device;

		VkQueue m_GraphicsQueue;

		VkSurfaceKHR m_Surface;

		std::vector<const char*> m_Extensions;
		std::vector<const char*> m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

	};

}
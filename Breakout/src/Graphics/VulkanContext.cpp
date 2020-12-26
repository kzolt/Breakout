#include "bkout.h"

#include "System/Window.h"
#include "VulkanContext.h"

#include <vulkan/vulkan_win32.h>

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		LOG_ERROR(pCallbackData->pMessage);

	return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

namespace Breakout {

	VulkanContext::VulkanContext(Window* window)
	{
		/////////////////////////////////////
		// Application Data Structures
		/////////////////////////////////////
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Breakout";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_2;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		/////////////////////////////////////
		// Extensions
		/////////////////////////////////////
		uint32_t extensionCount = 0;
		std::vector<VkExtensionProperties> extensionProperties;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		extensionProperties.resize(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());

#ifdef _DEBUG
		LOG_TRACE("Extensions: ");
		for (const auto& extension : extensionProperties)
			LOG_TRACE(extension.extensionName);
#endif

		for (const auto& extension : extensionProperties)
			m_Extensions.push_back(extension.extensionName);

		m_Extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_Extensions.size());
		createInfo.ppEnabledExtensionNames = m_Extensions.data();

#ifdef ENABLE_VALIDATION_LAYERS
		/////////////////////////////////////
		// Validation Layers
		/////////////////////////////////////
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		if (!CheckValidationLayers(availableLayers))
			LOG_WARN("Validation layers requested, but not available!");

		createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
		createInfo.ppEnabledLayerNames = m_ValidationLayers.data();

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
		PopulateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;

		LOG_INFO("Using Validation Layers");
#else
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
#endif

		ASSERT(!vkCreateInstance(&createInfo, nullptr, &m_Instance), "Could not create Vulkan Instance");

#ifdef _DEBUG
		/////////////////////////////////////
		// Vulkan Debugger
		/////////////////////////////////////
		SetupDebugger();
#endif
		/////////////////////////////////////
		// Create Windows Surface
		/////////////////////////////////////
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.hwnd = window->GetHandle();
		surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

		ASSERT(!vkCreateWin32SurfaceKHR(m_Instance, &surfaceCreateInfo, nullptr, &m_Surface), "Failed to create window surface!");

		/////////////////////////////////////
		// Pick Physical Device
		/////////////////////////////////////
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

		ASSERT(deviceCount, "Failed to find GPUs with Vulkan Support");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

		// Just use the first device we queried because breakout isn't graphically intensive at all, no point in doing anything else
		m_PhysicalDevice = devices[0];
		ASSERT(m_PhysicalDevice, "Failed to find a suitable GPU!");

		/////////////////////////////////////
		// Create Logical Device
		/////////////////////////////////////
		CreateDevice();
	}

	VulkanContext::~VulkanContext()
	{
		vkDestroyDevice(m_Device, nullptr);

#ifdef ENABLE_VALIDATION_LAYERS
		DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
#endif

		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
		vkDestroyInstance(m_Instance, nullptr);
	}

	bool VulkanContext::CheckValidationLayers(const std::vector<VkLayerProperties>& layers)
	{
		bool layerFound = false;

		for (const char* layerName : m_ValidationLayers)
		{
			for (const auto& layerProperties : layers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}
		}

		return layerFound;
	}

	void VulkanContext::SetupDebugger()
	{
		VkDebugUtilsMessengerCreateInfoEXT createInfo{};
		PopulateDebugMessengerCreateInfo(createInfo);

		ASSERT(!CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger), "Could not create Debug Messenger");
	}

	void VulkanContext::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;
	}

	QueueFamilyIndices VulkanContext::FindQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				indices.GraphicsFamily = i;

			i++;
		}

		return indices;
	}

	void VulkanContext::CreateDevice()
	{
		QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.GraphicsFamily.value();
		queueCreateInfo.queueCount = 1;

		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;

		createInfo.pEnabledFeatures = &deviceFeatures;

		ASSERT(!vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device), "Could not create Device!");
		vkGetDeviceQueue(m_Device, indices.GraphicsFamily.value(), 0, &m_GraphicsQueue);
	}

}
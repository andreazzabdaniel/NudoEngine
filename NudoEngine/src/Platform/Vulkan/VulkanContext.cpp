#include "ndpch.h"
#include  "Nudo/Core.h"
#include "VulkanContext.h"
#include "Nudo/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Nudo
{
	GraphicsContext* GraphicsContext::Create(void* nativeWindow)
	{
		return new VulkanContext(nativeWindow);
	}

	VulkanContext::~VulkanContext()
	{
		// ---------------------- Validation Layer ----------------------
		if (m_EnableValidation)
			VulkanDebug::Cleanup(m_Instance);
		// ---------------------- Validation Layer ----------------------

		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
		vkDestroyInstance(m_Instance, nullptr);
	}

	void VulkanContext::Init()
	{
		try
		{
			CreateInstance();

			// ---------------------- Validation Layer ----------------------
			if (m_EnableValidation)
				VulkanDebug::Setup(m_Instance);
			// ---------------------- Validation Layer ----------------------

			CreateSurface();

			m_Device = std::make_unique<VulkanDevice>(m_Instance, m_Surface);
			m_SwapChain = std::make_unique<VulkanSwapChain>();
		}
		catch (const std::exception& e)
		{
			printf("ERROR: %s", e.what());
		}
	}

	void VulkanContext::CreateSurface()
	{
		// Create a surface info struct, run the create surface function, returns vulkan result
		VkResult result = glfwCreateWindowSurface(
			m_Instance,
			static_cast<GLFWwindow*>(m_NativeWindow),
			nullptr,
			&m_Surface);

		if (result!= VK_SUCCESS)
			throw std::runtime_error("Failed to create surface!");
	}

	void VulkanContext::CreateInstance()
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType =					VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName =		"App Nudo";						// Application Name
		appInfo.applicationVersion =	VK_MAKE_VERSION(0, 0, 1);		// Application Version
		appInfo.pEngineName =			"Eng Nudo";						// Engine Name
		appInfo.engineVersion =			VK_MAKE_VERSION(0, 0, 1);		// Engine Version
		appInfo.apiVersion =			VK_API_VERSION_1_4;				// Vulkan Version

		// Cria��o da Informa��o para a vkInstance
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// Create list to hold instance extensions
		std::vector<const char*> instanceExtencions;

		// Setup extencions Instances extencions
		uint32_t glfwExtencionCount = 0;
		const char** glfwExtencions;

		glfwExtencions = glfwGetRequiredInstanceExtensions(&glfwExtencionCount);

		for (size_t i = 0; i < glfwExtencionCount; i++)
		{
			instanceExtencions.push_back(glfwExtencions[i]);
		}


		// ---------------------- Validation Layer ----------------------
		if (m_EnableValidation)
			instanceExtencions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		// ---------------------- Validation Layer ----------------------


		if (!checkInstanceExtensionsSupport(&instanceExtencions))
			throw std::runtime_error("Vulkan does not supor required INSTANCE extencion!");


		createInfo.enabledExtensionCount =		static_cast<uint32_t>(instanceExtencions.size());
		createInfo.ppEnabledExtensionNames =	instanceExtencions.data();

		// ---------------------- Validation Layer ----------------------
		if (m_EnableValidation && checkValidationLayerSupport())
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
			createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
			createInfo.ppEnabledLayerNames = nullptr;
		}
		// ---------------------- Validation Layer ----------------------


		// CreateInstance
		VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Fail to create Vulkan Instance");
		}
	}


	bool VulkanContext::checkInstanceExtensionsSupport(std::vector<const char*>* checkExtencions)
	{
		// Populate the number of extencions supported
		uint32_t extencionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extencionCount, nullptr);

		// Create a list the size of extencionCount
		std::vector<VkExtensionProperties> extencions(extencionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extencionCount, extencions.data());

		// Check if my extencions are in list of available extencions
		for (const auto& checkExtencion : *checkExtencions)
		{
			bool hasExtencion = false;

			for (const auto& extencion : extencions)
			{
				if (strcmp(checkExtencion, extencion.extensionName) == 0)
				{
					hasExtencion = true;
					break;
				}
			}

			if (!hasExtencion)
			{
				return false;
			}
		}

		return true;
	}





	// ---------------------- Validation Layer ----------------------
	bool VulkanContext::checkValidationLayerSupport()
	{
		uint32_t layerCount = 0;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* name : m_ValidationLayers)
		{
			bool found = false;
			for (const auto& layer : availableLayers)
			{
				if (strcmp(name, layer.layerName) == 0)
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				ND_CORE_WARN("Validation layer '{0}' not found � install Vulkan SDK", name);
				return false;
			}
		}
		return true;
	}
}


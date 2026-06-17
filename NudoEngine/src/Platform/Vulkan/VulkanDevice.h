#pragma once

#include <set>
#include <vulkan/vulkan.h>

#include "Utilities.h"

namespace Nudo
{
	class VulkanDevice
	{
	public:
		VulkanDevice(VkInstance instance, VkSurfaceKHR surface);
		~VulkanDevice();

		inline VkPhysicalDevice		GetPhysicalDevice()			{ return m_PhysicalDevice; }
		inline VkDevice				GetDevice()					{ return m_Device; }
		inline QueueFamilyIndices	GetQueueFamiliesIndices()	{ return m_Indices; }


		inline VkQueue		GetGraphicsQueue()			{ return m_GraphicsQueue; }
		inline VkQueue		GetPresentationQueue()		{ return m_PresentationQueue; }

	private:
		VkPhysicalDevice	m_PhysicalDevice	= VK_NULL_HANDLE;
		VkDevice			m_Device			= VK_NULL_HANDLE;
		VkQueue				m_GraphicsQueue		= VK_NULL_HANDLE;
		VkQueue				m_PresentationQueue = VK_NULL_HANDLE;
		QueueFamilyIndices	m_Indices;


		const std::vector<const char*> deviceExtencions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};


		// Create Func
		void CreateLogicalDevice();

		// Utils Func
		bool checkDeviceExtencionSupport(VkPhysicalDevice device);
		bool checkDeviceSuitable(VkPhysicalDevice device, QueueFamilyIndices indices);
		QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
	};
}

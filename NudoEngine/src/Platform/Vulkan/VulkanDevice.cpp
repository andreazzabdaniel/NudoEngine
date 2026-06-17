#include "ndpch.h"
#include "VulkanDevice.h"

namespace Nudo
{
	// TODO - We need to check more complex terms of device to optimize the best one to use. Usualy we select the
	// device based on score.
	// TODO - Create a system of queues with more control and with specialized features. 
	// TODO - Create a Queue management system with semaphores and fences to make it automatically


	VulkanDevice::VulkanDevice(VkInstance instance, VkSurfaceKHR surface)
	{
		// Enumerate Physical devices the vkInstance can access
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if (deviceCount == 0)
			throw std::runtime_error("No GPU support for vulkan instance");

		std::vector<VkPhysicalDevice> deviceList(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, deviceList.data());

		for (const auto& device : deviceList)
		{
			QueueFamilyIndices indices = getQueueFamilies(device, surface);
			if (checkDeviceSuitable(device, indices))
			{
				m_PhysicalDevice = device;
				m_Indices = indices;
				break;
			}
		}

		if (m_PhysicalDevice == VK_NULL_HANDLE)
			throw std::runtime_error("Failed to find a suitable GPU!");

		CreateLogicalDevice();
	}

	VulkanDevice::~VulkanDevice()
	{
		vkDestroyDevice(m_Device, nullptr);
	}

	void VulkanDevice::CreateLogicalDevice()
	{
		// Vector for creation of queue and set to verify if the indice are the same
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<int> queueFamilyIndices = { (int)m_Indices.graphicsFamily, (int)m_Indices.presentationFamily };


		// Queues the logical device need to create
		for (int queueFamilyIndex : queueFamilyIndices)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
			queueCreateInfo.queueCount = 1;
			float priority = 1.0f;
			queueCreateInfo.pQueuePriorities = &priority;

			queueCreateInfos.push_back(queueCreateInfo);
		}


		// Information to create device
		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());		// Number of queue createInfo
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();								// List of queue create infos
		deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtencions.size());	// Number of enabled device extencions
		deviceCreateInfo.ppEnabledExtensionNames = deviceExtencions.data();							// List of enabled device extencions
		deviceCreateInfo.enabledLayerCount = 0;

		VkPhysicalDeviceFeatures deviceFeatures = {};						// Lista de features do device not implemented yet

		deviceCreateInfo.pEnabledFeatures = &deviceFeatures;				// TODO - Implement in the future

		// Create the Device from the physical one
		VkResult result = vkCreateDevice(m_PhysicalDevice, &deviceCreateInfo, nullptr, &m_Device);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Device!");
		}

		// Queues are created with device, we need to handle the queues
		vkGetDeviceQueue(m_Device, m_Indices.graphicsFamily,     0, &m_GraphicsQueue);
		vkGetDeviceQueue(m_Device, m_Indices.presentationFamily, 0, &m_PresentationQueue);
	}



	bool VulkanDevice::checkDeviceSuitable(VkPhysicalDevice device, QueueFamilyIndices indices)
	{
		// Device info (ID, name, type, Vendor, device limits(max dimensions img, max push const, max uni buff))
		// TODO - Verify the device with all the features and support that my application will support
		VkPhysicalDeviceProperties deviceProps;
		vkGetPhysicalDeviceProperties(device, &deviceProps);

		// Device GPU features (geo shader, tess shader, wideLines, etc)
		// TODO - Verify if the features that application use is supported by device
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		bool extencionSupported = checkDeviceExtencionSupport(device);

		return indices.isValid() && extencionSupported;
	}

	QueueFamilyIndices VulkanDevice::getQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyList.data());

		// Go through each queue family and check if have at least 1 of the required types of queue
		int i = 0;
		for (const auto& queueFamily : queueFamilyList)
		{
			if (queueFamily.queueCount > 0 && (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT))
			{
				indices.graphicsFamily = i;
			}

			// Verify if suports presentation queue for the surface
			VkBool32 presentationSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentationSupport);
			if (queueFamily.queueCount > 0 && presentationSupport)
			{
				indices.presentationFamily = i;
			}

			if (indices.isValid())
			{
				break;
			}

			i++;
		}

		return indices;
	}


	bool VulkanDevice::checkDeviceExtencionSupport(VkPhysicalDevice device)
	{
		uint32_t extencionCount = 0;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extencionCount, nullptr);

		if (extencionCount == 0)
			return false;

		std::vector<VkExtensionProperties> extencions(extencionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extencionCount, extencions.data());

		// Utils deviceExtencion
		for (const auto& deviceExtencion : deviceExtencions)
		{
			bool hasExtencion = false;
			for (const auto &extencion : extencions)
			{
				if (strcmp(deviceExtencion, extencion.extensionName) == 0)
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
}


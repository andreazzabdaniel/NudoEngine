#include "ndpch.h"
#include "VulkanSwapChain.h"


namespace Nudo
{
	VulkanSwapChain::VulkanSwapChain(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		getSwapChainDetail(device, surface);
	}

	VulkanSwapChain::~VulkanSwapChain()
	{

	}

	SwapChainDetails VulkanSwapChain::getSwapChainDetail(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		SwapChainDetails swapChainDetails;

		// Get surface capabilities for given device
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &swapChainDetails.surfaceCapabilities);

		// Get formats suported
		uint32_t formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			swapChainDetails.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, swapChainDetails.formats.data());
		}


		// Presentation modes
		uint32_t presentationCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentationCount, nullptr);

		if (presentationCount != 0)
		{
			swapChainDetails.presentationModes.resize(presentationCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentationCount, swapChainDetails.presentationModes.data());
		}


		return swapChainDetails;
	}
}

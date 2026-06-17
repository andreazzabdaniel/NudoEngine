#pragma once

#include <vulkan/vulkan.h>

namespace Nudo
{
	class VulkanSwapChain
	{
	public:
		VulkanSwapChain(VkPhysicalDevice device, VkSurfaceKHR surface);
		~VulkanSwapChain();

	private:


		SwapChainDetails getSwapChainDetail(VkPhysicalDevice device, VkSurfaceKHR surface);
	};

	struct SwapChainDetails
	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentationModes;
	};
}
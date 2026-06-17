#pragma once

#include <vulkan/vulkan.h>

#include "Nudo/Renderer/GraphicsContext.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanDebug.h"

namespace Nudo
{
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(void* nativeWindow)
			: m_NativeWindow(nativeWindow) { }
		~VulkanContext();

		void Init() override;

	private:
		void*			m_NativeWindow	= nullptr;
		VkInstance		m_Instance		= VK_NULL_HANDLE;
		VkSurfaceKHR	m_Surface		= VK_NULL_HANDLE;


		std::unique_ptr<VulkanDevice>		m_Device;
		std::unique_ptr<VulkanSwapChain>	m_SwapChain;


		// ---------------------- Validation Layer ----------------------
		#ifdef NUDO_DEBUG
			const bool m_EnableValidation = true;
		#else
			const bool m_EnableValidation = false;
		#endif
			const std::vector<const char*> m_ValidationLayers = {
				"VK_LAYER_KHRONOS_validation"
			};
		// ---------------------- Validation Layer ----------------------


		// VK Functions
		// -- Create Functions
		void CreateInstance();
		void CreateSurface();

		// -- Support Functions
		bool checkInstanceExtensionsSupport(std::vector<const char*>* checkExtencions);
		bool checkValidationLayerSupport(); // <- Validation
	};
}

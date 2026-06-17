#pragma once

#include <vulkan/vulkan.h>

namespace Nudo
{
    class VulkanDebug
    {
    public:
        static void Setup(VkInstance instance);
        static void Cleanup(VkInstance instance);

    private:
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT      severity,
            VkDebugUtilsMessageTypeFlagsEXT             type,
            const VkDebugUtilsMessengerCallbackDataEXT* data,
            void* userdata);

        static VkDebugUtilsMessengerEXT s_Messenger;
    };
}
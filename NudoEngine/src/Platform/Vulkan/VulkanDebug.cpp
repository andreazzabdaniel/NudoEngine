#include "ndpch.h"

#include "Nudo/Core.h"
#include "VulkanDebug.h"

#include <vulkan/vulkan.h>

namespace Nudo
{
    VkDebugUtilsMessengerEXT VulkanDebug::s_Messenger = VK_NULL_HANDLE;

    // Funções de extensão não carregadas automaticamente — precisam ser buscadas
    static VkResult CreateDebugMessenger(
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* info, 
        VkDebugUtilsMessengerEXT* messenger)
    {
        auto fn = (PFN_vkCreateDebugUtilsMessengerEXT)
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        return fn ? fn(instance, info, nullptr, messenger) : VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    static void DestroyDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT messenger)
    {
        auto fn = (PFN_vkDestroyDebugUtilsMessengerEXT)
            vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (fn) fn(instance, messenger, nullptr);
    }

    void VulkanDebug::Setup(VkInstance instance)
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        // Quais severidades acionar o callback
        createInfo.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        // Quais tipos de mensagem capturar
        createInfo.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        createInfo.pfnUserCallback = DebugCallback;

        CreateDebugMessenger(instance, &createInfo, &s_Messenger);
    }

    void VulkanDebug::Cleanup(VkInstance instance)
    {
        DestroyDebugMessenger(instance, s_Messenger);
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebug::DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT      severity,
        VkDebugUtilsMessageTypeFlagsEXT             type,
        const VkDebugUtilsMessengerCallbackDataEXT* data,
        void* userdata)
    {
        if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
            ND_CORE_ERROR("Vulkan: {0}", data->pMessage);
        else
            ND_CORE_WARN("Vulkan: {0}", data->pMessage);

        return VK_FALSE;  // nunca abortar a chamada Vulkan aqui
    }
}
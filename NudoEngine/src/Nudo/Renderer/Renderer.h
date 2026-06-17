#pragma once


/*
O que falta em Platform/Vulkan/

Grupo 1 — Standalone (detalhes internos do Vulkan, sem interface em Renderer/)
São classes que só existem para organizar a inicialização do Vulkan. Nenhuma delas tem par em Renderer/. Só o VulkanContext as conhece.

    Arquivo	                    Responsabilidade
    --------------------------------------------------------------------------------------------------------------
    VulkanDevice.h/.cpp	        Seleciona a GPU física, cria o device lógico e as filas (graphics, present, transfer)
    VulkanSwapChain.h/.cpp	    Gerencia as imagens que aparecem na tela, resize, present modes
    VulkanAllocator.h/.cpp	    Inicializa o VMA, expõe vmaCreateBuffer e vmaCreateImage
    VulkanCommandBuffer.h/.cpp	Gerencia VkCommandPool e gravação/submissão de comandos
    VulkanDebug.h/.cpp	        Validation layers, debug messenger — só existe em Debug build


Grupo 2 — Implementações (têm interface em Renderer/)
São as classes que implementam as interfaces abstratas. Cada uma tem um par em Nudo/Renderer/.

    Arquivo Platform/Vulkan/	    Implementa interface em Renderer/
    ----------------------------------------------------------------------------------------------------------
    VulkanBuffer.h/.cpp	            Buffer.h — VertexBuffer, IndexBuffer, UniformBuffer
    VulkanShader.h/.cpp	            Shader.h — carrega SPIR-V, cria VkShaderModule
    VulkanTexture.h/.cpp	        Texture.h — cria VkImage, VkImageView, VkSampler
    VulkanFramebuffer.h/.cpp	    Framebuffer.h — cria VkFramebuffer
    VulkanPipeline.h/.cpp	        Pipeline.h — compila VkPipeline + VkPipelineLayout
    VulkanRenderPass.h/.cpp	        RenderPass.h — cria VkRenderPass, define attachments
    VulkanVertexArray.h/.cpp	    VertexArray.h — agrupa buffers e layout de vértice
    VulkanDescriptorSet.h/.cpp	    (sem interface) — gerencia VkDescriptorPool/Set/Layout


Visualmente
    Renderer/                        Platform/Vulkan/
    ?????????????????                ??????????????????????????????
    GraphicsContext.h   ?????????    VulkanContext.h/.cpp
                                         possui ? VulkanDevice.h/.cpp
                                         possui ? VulkanSwapChain.h/.cpp
                                         possui ? VulkanAllocator.h/.cpp
                                         possui ? VulkanCommandBuffer.h/.cpp
                                         possui ? VulkanDebug.h/.cpp
    Buffer.h            ?????????    VulkanBuffer.h/.cpp
    Shader.h            ?????????    VulkanShader.h/.cpp
    Texture.h           ?????????    VulkanTexture.h/.cpp
    Framebuffer.h       ?????????    VulkanFramebuffer.h/.cpp
    Pipeline.h          ?????????    VulkanPipeline.h/.cpp
    RenderPass.h        ?????????    VulkanRenderPass.h/.cpp
    VertexArray.h       ?????????    VulkanVertexArray.h/.cpp
    (sem interface)                  VulkanDescriptorSet.h/.cpp


Ordem de implementação recomendada

    1. VulkanDebug        ? validation layers primeiro, para ver erros desde o início
    2. VulkanDevice       ? selecionar GPU
    3. VulkanContext      ? juntar Instance + Surface + Device
    4. VulkanAllocator    ? VMA, necessário para qualquer buffer
    5. VulkanSwapChain    ? para ter algo na tela
    6. VulkanCommandBuffer? para poder gravar comandos
    7. VulkanRenderPass   ? necessário antes do pipeline
    8. VulkanPipeline     ? necessário para desenhar
    9. VulkanBuffer       ? dados de vértice
    10. VulkanShader      ? código que roda na GPU
    11. VulkanVertexArray ? agrupa buffers
    12. VulkanFramebuffer ? render targets
    13. VulkanTexture     ? imagens
    14. VulkanDescriptorSet ? binding de recursos ao shader
*/

namespace Nudo
{
    // TODO - Instalar VMA quando for mecher com buffers, pesquisar
    //  mais sobre isso, se é o padrão e se posso usar no projeto.
    // Quando chegar nessa parte de buffers do curso verificar isso.


}

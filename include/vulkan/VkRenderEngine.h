#ifndef RENDER_ENGINE_VULKAN_VKRENDERENGINE_H
#define RENDER_ENGINE_VULKAN_VKRENDERENGINE_H

#if defined (_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined (__linux__)
#define VK_USE_PLATFORM_XCB_KHR
#endif
#include <vulkan/vulkan.hpp>
#include <VkBootstrap.h>
#include "RenderEngine.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "VkGraphicsPass.h"
#include "VkGraphicsPass.h"
#include "vulkan/VmaUniqueAllocator.h"


class VkRenderEngine : public RenderEngine {
public:
    VkRenderEngine();
    virtual SuccessCode init();
    virtual SuccessCode render_scene();
    ~VkRenderEngine();

private:
    vk::SurfaceKHR _surface;
    vk::Instance _instance;
    vk::Device _device;
    vk::PhysicalDevice _physical_device;
    VkGraphicsPass _graphics_pass;
    PresentPass _present_pass;
    UniqueAllocator _allocator;
    Buffer _vertex_buffer;
    SuccessCode make_device();
};

#endif // RENDER_ENGINE_VULKAN_VKRENDERENGINE_H

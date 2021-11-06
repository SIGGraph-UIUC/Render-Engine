#ifndef RENDER_ENGINE_VKRENDERENGINE_H
#define RENDER_ENGINE_VKRENDERENGINE_H

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

    SuccessCode choose_device();
};

#endif // RENDER_ENGINE_VKRENDERENGINE_H

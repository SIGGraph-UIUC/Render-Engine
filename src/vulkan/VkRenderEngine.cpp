#include "vulkan/VkRenderEngine.h"
#include "vulkan/Utils.h"
#include <iostream>

VkRenderEngine::VkRenderEngine() {}

SuccessCode VkRenderEngine::init() {
    RenderEngine::init();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    _window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
    if (_window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        return SuccessCode::FAILURE;
    }

    auto result = make_device();
    if (result != SuccessCode::SUCCESS) {
        return result;
    }
    _allocator = Utils::make_allocator(_instance, _physical_device, _device);
//    VkGraphicsPass(VmaAllocator allocator, vk::PhysicalDevice physical_device, vk::Device device,
//                   vk::SurfaceKHR surface, const PresentPass & present_pass);
    _present_pass = PresentPass{_physical_device, _device, _surface, _window, 2};
    _graphics_pass = VkGraphicsPass{*_allocator, _physical_device, _device, _surface, _present_pass};
    return SuccessCode::SUCCESS;
}

SuccessCode VkRenderEngine::render_scene() {
    std::cout << "VULKAN ENGINE" << std::endl;
    return SuccessCode::SUCCESS;
}

VkRenderEngine::~VkRenderEngine() {
    _device.destroy();
    _instance.destroySurfaceKHR(_surface);
    _instance.destroy();
}

SuccessCode VkRenderEngine::make_device() {
    vkb::InstanceBuilder instance_builder;
    auto instance_ret = instance_builder.set_app_name("Render Engine")
            .request_validation_layers()
            .use_default_debug_messenger()
            .build();
    if (!instance_ret) {
        std::cerr << "Instance creation failed:" << instance_ret.error().message() << '\n';
        return SuccessCode::FAILURE;
    }
    _instance = instance_ret.value().instance;
    VkSurfaceKHR surface;
    if(glfwCreateWindowSurface(_instance, _window, nullptr, &surface) != VK_SUCCESS){
        return SuccessCode::FAILURE;
    }

    _surface = surface;

//#if defined (_WIN32)
//    vk::Win32SurfaceCreateInfoKHR surfaceCreateInfo{{}, (HINSTANCE) glfwGetWin32Window(_window),
//                                                    (HWND) GetModuleHandle(nullptr)};
//    _surface = _instance.createWin32SurfaceKHR(surfaceCreateInfo);
//#elif defined (__linux__)
//
//#endif

    vkb::PhysicalDeviceSelector physical_device_selector{instance_ret.value()};
    auto selected_device = physical_device_selector.set_minimum_version(1, 2)
            .set_surface(static_cast<VkSurfaceKHR>(_surface))
            .select();
    _physical_device = selected_device.value().physical_device;

    vkb::DeviceBuilder device_builder{selected_device.value()};
    auto device = device_builder.build();
    _device = device.value().device;

    return SuccessCode::SUCCESS;
}
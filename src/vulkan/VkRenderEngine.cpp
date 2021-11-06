#include "vulkan/VkRenderEngine.h"
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

#if defined (_WIN32)
    vk::Win32SurfaceCreateInfoKHR surfaceCreateInfo{{}, (HINSTANCE)glfwGetWin32Window(_window),
						    (HWND)GetModuleHandle(nullptr)};
    _surface = _instance.createWin32SurfaceKHR(surfaceCreateInfo);
#elif defined (__linux__)

#endif 

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
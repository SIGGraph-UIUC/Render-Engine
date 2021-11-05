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

VkRenderEngine::~VkRenderEngine() {}

SuccessCode VkRenderEngine::choose_device() {
    return SuccessCode::SUCCESS;
}
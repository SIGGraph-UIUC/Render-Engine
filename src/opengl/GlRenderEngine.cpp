#include "opengl/GlRenderEngine.h"
#include <iostream>

GlRenderEngine::GlRenderEngine() {}

SuccessCode GlRenderEngine::init() {
    RenderEngine::init();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (_window == NULL) {
	std::cout << "Failed to create window" << std::endl;
	return SuccessCode::FAILURE;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
	return SuccessCode::FAILURE;
    }
}

SuccessCode GlRenderEngine::render_scene() {
    std::cout << "OPENGL ENGINE" << std::endl;
    return SuccessCode::SUCCESS;
}

GlRenderEngine::~GlRenderEngine() {}
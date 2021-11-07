#include "RenderEngine.h"
#include "opengl/GlRenderEngine.h"
#include "vulkan/VkRenderEngine.h"
#include <iostream>

std::unique_ptr<RenderEngine> RenderEngine::make_engine(EngineType type) {
  switch (type) {
  case EngineType::VULKAN: {
    std::cout << "CREATING VULKAN ENGINE" << std::endl;
    return std::unique_ptr<RenderEngine>(new VkRenderEngine());
  }
  case EngineType::OPENGL: {
    std::cout << "CREATING OPENGL ENGINE" << std::endl;
    return std::unique_ptr<RenderEngine>(new GlRenderEngine());
  }
  default: {
    std::cerr << "Invalid engine type provided\n";
    return nullptr;
  }
  }
}

SuccessCode RenderEngine::init() {
  glfwInit();
  return SuccessCode::SUCCESS;
}

SuccessCode RenderEngine::draw() {
  while (!glfwWindowShouldClose(_window)) {
    glfwPollEvents();
    render_scene();
  }

  return SuccessCode::SUCCESS;
}

RenderEngine::~RenderEngine() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

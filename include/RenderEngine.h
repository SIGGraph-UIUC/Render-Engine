//
// Created by 16182 on 11/1/2021.
//

#ifndef RENDER_ENGINE_RENDERENGINE_H
#define RENDER_ENGINE_RENDERENGINE_H

#include "Enums.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>

class RenderEngine {
public:
  static std::unique_ptr<RenderEngine> make_engine(EngineType type);

  virtual SuccessCode init();
  SuccessCode draw();
  virtual SuccessCode render_scene() = 0; // for now just a spinning cube
  virtual ~RenderEngine();

protected:
    GLFWwindow* _window;
};

#endif // RENDER_ENGINE_RENDERENGINE_H

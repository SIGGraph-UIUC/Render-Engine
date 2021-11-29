#include "opengl/GlRenderEngine.h"
#include <iostream>
#include "opengl/GlShader.h"

GlRenderEngine::GlRenderEngine() = default;

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

    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
	    return SuccessCode::FAILURE;
    }


    glClearColor(0, 0, 1, 1);
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
    shader_ = Shader("src/shaders/tri.vert","src/shaders/tri.frag");

    return SuccessCode::SUCCESS;
}

SuccessCode GlRenderEngine::render_scene() {
    std::cout << "OPENGL ENGINE" << std::endl;
    shader_.use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glFlush();
    glfwSwapBuffers(_window);
    return SuccessCode::SUCCESS;
}

GlRenderEngine::~GlRenderEngine() {}
#ifndef RENDER_ENGINE_GLRENDERENGINE_H
#define RENDER_ENGINE_GLRENDERENGINE_H

#include "RenderEngine.h"

#include <glad/glad.h>
#include<opengl/GlShader.h>
class GlRenderEngine : public RenderEngine {
public:
    GlRenderEngine();
    virtual SuccessCode init();
    virtual SuccessCode render_scene();
    virtual ~GlRenderEngine();

    Shader shader_;
};

#endif // RENDER_ENGINE_GLRENDERENGINE_H
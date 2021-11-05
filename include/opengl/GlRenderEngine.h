#ifndef RENDER_ENGINE_GLRENDERENGINE_H
#define RENDER_ENGINE_GLRENDERENGINE_H

#include "RenderEngine.h"

#include <glad/glad.h>

class GlRenderEngine : public RenderEngine {
public:
    GlRenderEngine();
    virtual SuccessCode init();
    virtual SuccessCode render_scene();
    ~GlRenderEngine();
};

#endif // RENDER_ENGINE_GLRENDERENGINE_H
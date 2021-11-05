#ifndef RENDER_ENGINE_VKRENDERENGINE_H
#define RENDER_ENGINE_VKRENDERENGINE_H

#include "RenderEngine.h"

class VkRenderEngine : public RenderEngine {
public:
    VkRenderEngine();
    virtual SuccessCode init();
    virtual SuccessCode render_scene();
    ~VkRenderEngine();

private:
    SuccessCode choose_device();
};

#endif // RENDER_ENGINE_VKRENDERENGINE_H

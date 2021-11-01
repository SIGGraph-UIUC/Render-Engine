//
// Created by 16182 on 11/1/2021.
//

#include "enums.h"

#ifndef RENDER_ENGINE_RENDERENGINE_H
#define RENDER_ENGINE_RENDERENGINE_H

class RenderEngine {
public:
    static std::unique_ptr<RenderEngine> make_engine(EngineType);
    virtual SuccessCode init() = 0;
    virtual SuccessCode render_scene() = 0;//for now just a spinning cube
    virtual ~RenderEngine() = 0;
};

#endif //RENDER_ENGINE_RENDERENGINE_H

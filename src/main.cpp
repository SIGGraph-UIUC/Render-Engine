#include <iostream>
#include "RenderEngine.h"

int main(int argc, char* argv[]) {
    EngineType type = (argc == 1) ? EngineType::VULKAN : EngineType::OPENGL;
    auto engine = RenderEngine::make_engine(type);
    engine->init();
    engine->draw();
}

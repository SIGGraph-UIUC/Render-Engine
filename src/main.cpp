#include <iostream>

#include "RenderEngine.h"

int main(int argc, char* argv[]) {
//    EngineType type = (argc == 1) ? EngineType::VULKAN : EngineType::OPENGL;
    auto type = EngineType::OPENGL;
    auto engine = RenderEngine::make_engine(type);
    if(engine->init() != SuccessCode::SUCCESS){
        std::cerr << "init failed" << std::endl;
    };
    engine->draw();
}

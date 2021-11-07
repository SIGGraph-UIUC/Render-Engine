#ifndef RENDER_ENGINE_VULKAN_LOADASSETS_H
#define RENDER_ENGINE_VULKAN_LOADASSETS_H
#include<vector>
#include<tuple>
#include<cstdint>

namespace LoadAssets {
    [[nodiscard]] std::vector<char> read_file(const char *file_name);
};


#endif // RENDER_ENGINE_VULKAN_LOADASSETS_H

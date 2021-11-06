//
// Created by 16182 on 6/27/2021.
//

#include "vulkan/LoadAssets.h"
#include <stdexcept>
#include <fstream>

std::vector<char> LoadAssets::read_file(const char *file_name) {
    std::ifstream file(file_name, std::ios_base::ate | std::ios_base::binary);
    if(!file.is_open()){
        throw std::runtime_error("failed to open file");
    }
    size_t file_size = (size_t)file.tellg();
    file.seekg(0);
    std::vector<char> buffer(file_size);
    file.read(buffer.data(), file_size);

    return buffer;
}
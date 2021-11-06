//
// Created by 16182 on 6/27/2021.
//

#ifndef VULKANNOTINCLUDED_LOADASSETS_H
#define VULKANNOTINCLUDED_LOADASSETS_H
#include<vector>
#include<tuple>
#include<cstdint>

namespace LoadAssets {
    [[nodiscard]] std::vector<char> read_file(const char *file_name);
};


#endif //VULKANNOTINCLUDED_LOADASSETS_H

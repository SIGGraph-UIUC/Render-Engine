//
// Created by 16182 on 6/21/2021.
//

#ifndef VERTEX_H
#define VERTEX_H
#include<vulkan/vulkan.hpp>
#define GLM_FORCE_RADIANS
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>
#include<array>

struct UniformBufferObject {
    glm::mat4 ubo;
};

struct SpecilizationData {
    uint32_t BUFFER_ELEMENT_COUNT;
};

struct Vertex {
    alignas(16) glm::vec4 position;
    alignas(16) glm::vec4 normal;

    static vk::VertexInputBindingDescription binding_description() {
        VkVertexInputBindingDescription binding_description{
            .binding = 0,
            .stride = sizeof(Vertex),
            .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
            };
        return binding_description;
    }

    static std::array<vk::VertexInputAttributeDescription, 2> attribute_descriptions(){
        std::array<vk::VertexInputAttributeDescription, 2> attribute_descriptions{
            {
                {
                    0,
                    0,
                    vk::Format::eR32G32B32A32Sfloat,
                    offsetof(Vertex, position)
                    },
                    {
                    1,
                    0,
                    vk::Format::eR32G32B32A32Sfloat,
                    offsetof(Vertex, normal)
                    }
            }
        };
        return attribute_descriptions;
    }
};

#endif //VERTEX_H

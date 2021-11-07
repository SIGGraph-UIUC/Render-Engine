#ifndef RENDER_ENGINE_VULKAN_UTILS_H
#define RENDER_ENGINE_VULKAN_UTILS_H

#include <optional>
#include <cstdint>
#include <vulkan/vulkan.hpp>
#include "VmaUniqueAllocator.h"
#include "vk_mem_alloc.h"

namespace Utils {
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphics_family;
        std::optional<uint32_t> present_family;
        std::optional<uint32_t> compute_family;
        [[nodiscard]] bool complete() const;
    };
    QueueFamilyIndices find_queue_families(vk::PhysicalDevice physical_device, vk::SurfaceKHR surface);

    void gpu_memcpy_host_local(VmaAllocator allocator, VmaAllocation dst, void * data, size_t size);

    UniqueAllocator make_allocator(vk::Instance instance, vk::PhysicalDevice physical_device, vk::Device device);
};


#endif // RENDER_ENGINE_VULKAN_UTILS_H
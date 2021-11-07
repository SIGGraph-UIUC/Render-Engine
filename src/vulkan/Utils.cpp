#include <span>
#include "vulkan/Utils.h"

bool Utils::QueueFamilyIndices::complete() const {
    return graphics_family.has_value() && present_family.has_value() && compute_family.has_value();
}

Utils::QueueFamilyIndices Utils::find_queue_families(vk::PhysicalDevice physical_device, vk::SurfaceKHR surface) {
    QueueFamilyIndices indices{};
    std::vector<vk::QueueFamilyProperties> queue_families = physical_device.getQueueFamilyProperties();
    for(size_t i = 0; i < queue_families.size(); i++){
        if(queue_families[i].queueFlags & vk::QueueFlagBits::eGraphics){
            if(!indices.graphics_family.has_value())
                indices.graphics_family = i;
        }
        if(queue_families[i].queueFlags & vk::QueueFlagBits::eCompute){
            if(!indices.compute_family.has_value())
                indices.compute_family = i;
        }
        if(surface){
            auto present_support = physical_device.getSurfaceSupportKHR(i, surface);
            if(present_support) {
                if(!indices.present_family.has_value())
                    indices.present_family = i;
            }
        }
    }
    return indices;
}

void Utils::gpu_memcpy_host_local(VmaAllocator allocator, VmaAllocation dst, void *data, size_t size) {
    if(size == 0) return;
    //vmaMapMemory fails on cpu mapped memory where the memory region is 0 bytes
    void * write_ptr;
    auto result = vmaMapMemory(allocator, dst, &write_ptr);
    if(result != VK_SUCCESS){
        throw std::runtime_error("failed to map memory");
    }
    std::memcpy(write_ptr, data, size);
    vmaUnmapMemory(allocator, dst);
}

UniqueAllocator Utils::make_allocator(vk::Instance instance, vk::PhysicalDevice physical_device, vk::Device device) {
    VmaAllocatorCreateInfo create_info{
        .physicalDevice = physical_device,
        .device = device,
        .instance = instance,
        .vulkanApiVersion = VK_API_VERSION_1_2,
    };

    VmaAllocator allocator;
    vmaCreateAllocator(&create_info, &allocator);
    return UniqueAllocator(allocator);
}

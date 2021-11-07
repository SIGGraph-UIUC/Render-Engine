#ifndef RENDER_ENGINE_VULKAN_BUFFER_H
#define RENDER_ENGINE_VULKAN_BUFFER_H
#include <vk_mem_alloc.h>
#include <vulkan/vulkan.hpp>
class Buffer {
public:
    Buffer() = default;
    Buffer(VmaAllocator allocator, size_t size, vk::BufferUsageFlags buffer_usage, VmaMemoryUsage memory_usage){
        vk::BufferCreateInfo buffer_create_info{{}, size, buffer_usage};
        VmaAllocationCreateInfo allocation_create_info{.usage = memory_usage};
        vmaCreateBuffer(allocator, reinterpret_cast<VkBufferCreateInfo*>(&buffer_create_info),
                        &allocation_create_info, reinterpret_cast<VkBuffer*>(&_buffer), reinterpret_cast<VmaAllocation*>(&_allocation), nullptr);
        _size = size;
        _allocator = allocator;
    }
    Buffer(Buffer && src) noexcept : _buffer(src._buffer), _allocation(src._allocation), _allocator(src._allocator), _size(src._size){
        src._buffer = vk::Buffer{};
        src._allocation = {};
        src._allocator = {};
        src._size = {};
    }
    Buffer & operator=(Buffer && src) noexcept {
        _buffer = src._buffer;
        _allocation = src._allocation;
        _allocator = src._allocator;
        _size = src._size;
        src._buffer = vk::Buffer{};
        src._allocation = {};
        src._allocator = {};
        src._size = {};
        return *this;
    }
    Buffer(Buffer &) = delete;
    ~Buffer(){
        if(_buffer){
            assert(_buffer && _allocation && _allocator);
            vmaDestroyBuffer(_allocator, _buffer, _allocation);
        } else {
            assert(!_buffer && !_allocation && !_allocator);
        }
    }

    [[nodiscard]] vk::Buffer vkBuffer() const {
        return _buffer;
    }
    [[nodiscard]] size_t size() const {
        return _size;
    }
    [[nodiscard]] vk::DescriptorBufferInfo buffer_info() const {
        return {vkBuffer(), 0, size()};
    }
private:
    vk::Buffer _buffer{};
    VmaAllocation _allocation{};
    VmaAllocator _allocator{};
    size_t _size{};
};

#endif // RENDER_ENGINE_VULKAN_BUFFER_H

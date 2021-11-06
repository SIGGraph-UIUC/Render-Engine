#ifndef BUFFER_H
#define BUFFER_H
#include<vk_mem_alloc.h>
#include<vulkan/vulkan.hpp>
class Buffer {
public:
    Buffer() = default;
    Buffer(VmaAllocator allocator, size_t size, vk::BufferUsageFlags buffer_usage, VmaMemoryUsage memory_usage){
        VkBufferCreateInfo buffer_create_info{
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .flags = {},
            .size = size,
            .usage = (uint32_t)buffer_usage,
            };
        VmaAllocationCreateInfo allocation_create_info{
            .usage = memory_usage,
            };
        VkBuffer buffer;
        VmaAllocation allocation;
        vmaCreateBuffer(allocator, &buffer_create_info, &allocation_create_info, &buffer, &allocation, nullptr);
        _buffer = buffer;
        _size = size;
        _allocator = allocator;
        _allocation = allocation;
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

#endif //BUFFER_H

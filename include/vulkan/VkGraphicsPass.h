//
// Created by 16182 on 11/6/2021.
//

#ifndef RENDERENGINE_VKVkGraphicsPass_H
#define RENDERENGINE_VKVkGraphicsPass_H

#include<vulkan/vulkan.hpp>
#include<vk_mem_alloc.h>
#include "Buffer.h"
#include "Image.h"
#include "PresentPass.h"
class VkGraphicsPass {
public:
    VkGraphicsPass() = default;
    VkGraphicsPass(VkGraphicsPass &) = delete;
    VkGraphicsPass(VkGraphicsPass &&) = delete;
    VkGraphicsPass(VmaAllocator allocator, vk::PhysicalDevice physical_device, vk::Device device,
                   vk::SurfaceKHR surface, const PresentPass & present_pass);

    void record_begin_render(vk::CommandBuffer command_buffer, vk::Framebuffer frame_buffer);
    void record_push_constants(vk::CommandBuffer command_buffer, void * data, size_t size);
    void record_bind_descriptors(vk::CommandBuffer command_buffer, vk::DescriptorSet descriptor_set);
    void record_draw(vk::CommandBuffer command_buffer, Buffer const& vertex_buffer, size_t vertex_count);
    void record_draw_indexed(vk::CommandBuffer command_buffer, Buffer const& vertex_buffer, Buffer const& index_buffer, size_t index_count);
    void record_end_render(vk::CommandBuffer command_buffer);
    void write_descriptor(vk::DescriptorSet descriptor_set, Buffer & node_state_buffer);
    vk::UniqueCommandBuffer create_command_buffer();
    vk::UniqueDescriptorSet create_descriptor_set();
    vk::Framebuffer get_framebuffer(uint32_t index);
    vk::Queue queue(){
        return _queue;
    }
private:
    vk::UniquePipeline make_pipeline(vk::Device device, vk::Extent2D extent);
    vk::UniqueRenderPass make_render_pass(vk::Device device, vk::Format image_format, vk::Format depth_format);
    std::vector<vk::UniqueFramebuffer> make_framebuffers(std::vector<vk::ImageView> image_views);


    vk::Queue _queue;
    vk::Device _device;
    vk::Extent2D _extent;
    vk::UniquePipeline _pipeline;
    vk::UniquePipelineLayout _pipeline_layout;
    vk::UniqueDescriptorPool _descriptor_pool;
    vk::UniqueDescriptorSetLayout _descriptor_set_layout;
    vk::UniqueRenderPass _render_pass;
    vk::UniqueCommandPool _command_pool;
    vk::UniqueShaderModule _vert_shader, _frag_shader;
    vk::UniqueImageView _depth_image_view;
    std::vector<vk::UniqueFramebuffer> _frame_buffers;
    Image _depth_image;
};

#endif //RENDERENGINE_VKVkGraphicsPass_H

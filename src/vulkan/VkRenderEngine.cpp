#include "vulkan/VkRenderEngine.h"
#include "vulkan/Utils.h"
#include <iostream>

VkRenderEngine::VkRenderEngine() {}

SuccessCode VkRenderEngine::init() {
    RenderEngine::init();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    _window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
    if (_window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        return SuccessCode::FAILURE;
    }

    auto result = make_device();
    if (result != SuccessCode::SUCCESS) {
        return result;
    }
    _allocator = Utils::make_allocator(_instance, _physical_device, _device);
    //    VmaAllocator allocator, vk::Extent2D extent, vk::Format format, vk::ImageUsageFlags image_usage, vk::ImageAspectFlags aspect_mask, VmaMemoryUsage memory_usage
//    VkGraphicsPass(VmaAllocator allocator, vk::PhysicalDevice physical_device, vk::Device device,
//                   vk::SurfaceKHR surface, const PresentPass & present_pass);
    _present_pass = PresentPass{_physical_device, _device, _surface, _window, 2};

    _graphics_pass = VkGraphicsPass{*_allocator, _physical_device, _device, _surface, _present_pass};
    std::vector<float> vertices = {
            0,0,
            0.5,0.5,
            0.5,0
    };


    _vertex_buffer = {*_allocator, vertices.size() * sizeof(vertices[0]), vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, VMA_MEMORY_USAGE_GPU_ONLY};

    return SuccessCode::SUCCESS;
}

SuccessCode VkRenderEngine::render_scene() {
    static size_t frame_num = 0;
    frame_num++;
    uint32_t image_index = _present_pass.get_next_image_index();
    vk::UniqueCommandBuffer command_buffer = _graphics_pass.create_command_buffer();
    vk::CommandBufferBeginInfo begin_info{};

    auto descriptor_set = _graphics_pass.create_descriptor_set();
    command_buffer->begin(begin_info);
    _graphics_pass.record_begin_render(*command_buffer, _graphics_pass.get_framebuffer(image_index));
    _graphics_pass.record_draw(*command_buffer, _vertex_buffer, 3);
//    _graphics_pass.record_draw_indexed(*command_buffer, vertex_buffer, index_buffer, indices.size());
    //    _graphics.record_draw(*command_buffer, vertex_buffer, vertices.size());
    _graphics_pass.record_end_render(*command_buffer);
    command_buffer->end();

    vk::Semaphore wait_semaphores[] = {
            _present_pass.image_available_semaphore(),
            };
    vk::Semaphore signal_semaphores[] = {
            _present_pass.render_finished_semaphore()
    };
    vk::PipelineStageFlags wait_stages = vk::PipelineStageFlagBits::eColorAttachmentOutput;

    vk::SubmitInfo submit_info(
            std::size(wait_semaphores),
            wait_semaphores,
            &wait_stages,
            1,
            &*command_buffer,
            std::size(signal_semaphores),
            signal_semaphores
            );
    _device.resetFences(_present_pass.in_flight_fence());
    _graphics_pass.queue().submit(submit_info, _present_pass.in_flight_fence());
    _present_pass.present_image(image_index);
    _device.waitIdle();
    return SuccessCode::SUCCESS;
}

VkRenderEngine::~VkRenderEngine() {
    _device.destroy();
    _instance.destroySurfaceKHR(_surface);
    _instance.destroy();
}

SuccessCode VkRenderEngine::make_device() {
    vkb::InstanceBuilder instance_builder;
    auto instance_ret = instance_builder.set_app_name("Render Engine")
            .require_api_version(1,2,0)
            .request_validation_layers()
            .use_default_debug_messenger()
            .build();
    if (!instance_ret) {
        std::cerr << "Instance creation failed:" << instance_ret.error().message() << '\n';
        return SuccessCode::FAILURE;
    }
    _instance = instance_ret.value().instance;
    VkSurfaceKHR surface;
    if(glfwCreateWindowSurface(_instance, _window, nullptr, &surface) != VK_SUCCESS){
        return SuccessCode::FAILURE;
    }

    _surface = surface;

//#if defined (_WIN32)
//    vk::Win32SurfaceCreateInfoKHR surfaceCreateInfo{{}, (HINSTANCE) glfwGetWin32Window(_window),
//                                                    (HWND) GetModuleHandle(nullptr)};
//    _surface = _instance.createWin32SurfaceKHR(surfaceCreateInfo);
//#elif defined (__linux__)
//
//#endif

    vkb::PhysicalDeviceSelector physical_device_selector{instance_ret.value()};
    auto selected_device = physical_device_selector.set_minimum_version(1, 2)
            .set_surface(static_cast<VkSurfaceKHR>(_surface))
            .select();
    _physical_device = selected_device.value().physical_device;

    vkb::DeviceBuilder device_builder{selected_device.value()};
    auto device = device_builder.build();
    _device = device.value().device;

    return SuccessCode::SUCCESS;
}
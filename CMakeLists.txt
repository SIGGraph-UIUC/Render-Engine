cmake_minimum_required(VERSION 3.10)

project(RenderEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)

include_directories(include/
                    external/glad/include/
                    external
                    ${Vulkan_INCLUDE_DIR})

add_executable(${PROJECT_NAME} src/main.cpp src/RenderEngine src/RenderEngine.cpp src/vulkan/VkRenderEngine.cpp src/opengl/GlRenderEngine.cpp
               ${LIB_SOURCES})

target_link_libraries(${PROJECT_NAME}
                      glad glfw ${GLFW_LIBRARIES} glm
                      vk-bootstrap vma vulkan-hpp
                      ${Vulkan_LIBRARY})

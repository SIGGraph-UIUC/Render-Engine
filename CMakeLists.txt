cmake_minimum_required(VERSION 3.10)

project(RenderEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)

include_directories(include/
                    ${Vulkan_INCLUDE_DIR})

file(GLOB INTERFACE_SOURCES
    src/RenderEngine.cpp
)

file(GLOB OPENGL_ENGINE_SOURCES
    src/opengl/GlRenderEngine.cpp
)

file(GLOB VULKAN_ENGINE_SOURCES
    src/vulkan/VkRenderEngine.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp ${LIB_SOURCES}
               ${INTERFACE_SOURCES}
               ${OPENGL_ENGINE_SOURCES}
               ${VULKAN_ENGINE_SOURCES})

target_link_libraries(${PROJECT_NAME}
                      glad glfw ${GLFW_LIBRARIES} glm
                      vk-bootstrap vma vulkan-hpp
                      ${Vulkan_LIBRARY})

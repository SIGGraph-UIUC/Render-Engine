cmake_minimum_required(VERSION 3.10)

project(RenderEngine)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)

include_directories(include/
                    ${Vulkan_INCLUDE_DIR})

file(GLOB INTERFACE_SOURCES
    src/RenderEngine.cpp
)

file(GLOB OPENGL_ENGINE_SOURCES
    src/opengl/*.cpp
)

file(GLOB VULKAN_ENGINE_SOURCES
    src/vulkan/*.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp ${LIB_SOURCES}
               ${INTERFACE_SOURCES}
               ${OPENGL_ENGINE_SOURCES}
               ${VULKAN_ENGINE_SOURCES})

target_link_libraries(${PROJECT_NAME}
                      glad glfw ${GLFW_LIBRARIES} glm
                      vk-bootstrap vma ${Vulkan_LIBRARY})

cmake_minimum_required(VERSION 3.10)

project(RenderEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

include_directories(include/
                    external/glad/include/
                    external/glfw/include/
                    external/glm
                    external)

file(GLOB LIB_SOURCES
     external/glad/src/glad.c)

add_executable(${PROJECT_NAME} src/main.cpp src/RenderEngine src/RenderEngine.cpp src/vulkan/VkRenderEngine.cpp src/opengl/GlRenderEngine.cpp
               ${LIB_SOURCES})

target_link_libraries(${PROJECT_NAME}
                      glfw ${GLFW_LIBRARIES})

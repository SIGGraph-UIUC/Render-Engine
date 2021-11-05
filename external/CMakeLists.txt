find_package(Vulkan REQUIRED)

add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(glfw)

add_subdirectory(glm)

add_subdirectory(vk-bootstrap)

add_library(vma INTERFACE vma)

add_library(vulkan-hpp INTERFACE vulkan)

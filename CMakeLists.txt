cmake_minimum_required(VERSION 3.10)

project(RenderEngine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
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


add_custom_target(CompileShaders
        COMMAND ${CMAKE_SOURCE_DIR}/src/shaders/compile.bat)

#add_custom_target(CopyShaders
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shaders/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
#        DEPENDS CompileShaders
#        )

add_dependencies(${PROJECT_NAME} CompileShaders)


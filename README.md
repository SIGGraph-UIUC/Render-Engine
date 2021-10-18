Features:
Cross-Platform
Scene graph architecture
Materials 
DearImGui integration
Model loading
Lighting
Object picking
Anti-aliasing
Deferred rendering
Shadows
Culling
Multithreading

Standards:
clang-format
CMake 3.10 / C++17
OpenGL 3
Vulkan 1.2
GLFW
GLM
Assimp
DearImGui

Renderer Interface
    init/initialize
    Anti aliasing settings
    Lighting settings

Camera Interface
Set fov, position, direction    

Scene Interface
    set_camera 
    Modify_object
    render 
    add_object / hide_object / remove_object
    add_light / hide_light / remove_light

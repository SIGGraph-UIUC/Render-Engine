setlocal
cd /d "%~dp0"

glslc tri.vert -o tri.vert.spv -O -g --target-env=vulkan1.0
glslc tri.frag -o tri.frag.spv -O -g --target-env=vulkan1.0
@REM glslc comp.comp -o comp.comp.spv -O -g --target-env=vulkan1.2

endlocal
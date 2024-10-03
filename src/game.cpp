#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
constexpr int screenWidth = 800;

constexpr int screenHeight = 450;

int main(int argc, char **argv) {
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    glfwInit();
#endif
    return 0;
}

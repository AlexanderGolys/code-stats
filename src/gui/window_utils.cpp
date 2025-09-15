#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "window_utils.hpp"

void get_framebuffer_size(GLFWwindow* window, int& width, int& height)
{
    glfwGetFramebufferSize(window, &width, &height);
}

void set_viewport_to_framebuffer(GLFWwindow* window)
{
    int width, height;
    get_framebuffer_size(window, width, height);
    glViewport(0, 0, width, height);
}

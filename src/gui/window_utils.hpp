#pragma once
#include "isbell.hpp"
#include "nuklear.h"
#include "nuklear_glfw_gl4.h"

void get_framebuffer_size(GLFWwindow* window, int& width, int& height);
void set_viewport_to_framebuffer(GLFWwindow* window);

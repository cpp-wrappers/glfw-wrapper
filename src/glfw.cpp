#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "../include/glfw/glfw.hpp"

using namespace glfw;

void glfw::poll_events() {
    glfwPollEvents();
}

namespace glfw { namespace internal {
static error_callback_t error_callback;
}}

void glfw::error_callback(error_callback_t callback) {
    internal::error_callback = callback;
    glfwSetErrorCallback([](int code, const char* desc) {
        internal::error_callback({code, desc});
    });
}
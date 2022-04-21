#pragma once

#include "handle.hpp"

extern "C" GLFW_API void glfwDestroyWindow(handle<glfw::window> window);

namespace glfw {

	inline void destroy_window(handle<glfw::window> window) {
		glfwDestroyWindow(window);
	}

} // glfw
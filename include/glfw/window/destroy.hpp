#pragma once

#include "handle.hpp"

namespace glfw {

	inline void destroy_window(handle<glfw::window> window) {
		glfwDestroyWindow((GLFWwindow*) window.raw());
	}

} // glfw
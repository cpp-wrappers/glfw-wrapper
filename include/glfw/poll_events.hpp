#pragma once

#include "function.hpp"

extern "C" GLFW_API void glfwPollEvents();

namespace glfw {

	inline void poll_events() {
		glfwPollEvents();
	}

} // glfw
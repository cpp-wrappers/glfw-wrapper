#pragma once

#include "function.hpp"
#include "error.hpp"

extern "C" GLFW_API int glfwInit();

namespace glfw {

	inline bool try_init() {
		return glfwInit();
	}

} // glfw
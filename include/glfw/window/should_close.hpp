#pragma once

#include "handle.hpp"
#include "../function.hpp"

extern "C" GLFW_API int glfwWindowShouldClose(handle<glfw::window> window);

namespace glfw {

	bool inline window_should_close(handle<glfw::window> window) {
		return glfwWindowShouldClose(window);
	}

} // glfw

inline bool handle<glfw::window>::should_close() const {
	return glfw::window_should_close(*this);
}
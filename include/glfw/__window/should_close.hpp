#pragma once

#include "handle.hpp"
#include "../__internal/function.hpp"

extern "C" GLFW_API int glfwWindowShouldClose(
	handle<glfw::window>::underlying_type window
);

namespace glfw {

	bool inline window_should_close(handle<glfw::window> window) {
		return glfwWindowShouldClose(window.underlying());
	}

} // glfw

inline bool handle_interface<glfw::window>::should_close() const {
	return glfw::window_should_close(this->underlying());
}
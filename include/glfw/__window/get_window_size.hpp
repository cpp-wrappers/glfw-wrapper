#pragma once

#include "handle.hpp"
#include "../__internal/function.hpp"

#include <math/vector.hpp>

extern "C" GLFW_API void glfwGetWindowSize(
	handle<glfw::window>::underlying_type window,
	int* width, int* height
);

namespace glfw {

	inline math::vector<int, 2> get_window_size(
		handle<glfw::window> window
	) {
		int w, h;
		glfwGetWindowSize(window.underlying(), &w, &h);
		return { w, h };
	}

} // glfw

math::vector<int, 2> handle_interface<glfw::window>::get_size() const {
	return glfw::get_window_size(this->underlying());
}
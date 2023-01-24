#pragma once

#include "handle.hpp"
#include "../__internal/function.hpp"

#include <math/vector.hpp>

extern "C" GLFW_API void glfwGetCursorPos(
	handle<glfw::window>::underlying_type window,
	double* xpos,
	double* ypos
);

namespace glfw {

	inline math::vector<double, 2> get_cursor_pos(
		handle<glfw::window> window
	) {
		double x, y;
		glfwGetCursorPos(window.underlying(), &x, &y);
		return { x, y };
	}

} // glfw

math::vector<double, 2> handle_interface<glfw::window>::get_cursor_pos() const {
	return glfw::get_cursor_pos(this->underlying());
}
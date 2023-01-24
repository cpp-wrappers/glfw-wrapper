#pragma once

#include "handle.hpp"

#include <body.hpp>

extern "C" GLFW_API void glfwDestroyWindow(
	handle<glfw::window>::underlying_type window
);

namespace glfw {

	inline void destroy(handle<glfw::window> window) {
		glfwDestroyWindow(window.underlying());
	}

} // glfw

template<>
inline void body<glfw::window>::do_destroy() {
	glfw::destroy(this->handle());
}
#pragma once

#include "handle.hpp"
#include "../headers.hpp"

#include <core/handle/possibly_guarded_of.hpp>

namespace glfw {

	bool window_should_close(possibly_guarded_handle_of<glfw::window> auto&& handle) {
		return glfwWindowShouldClose(handle.raw());
	}

} // glfw
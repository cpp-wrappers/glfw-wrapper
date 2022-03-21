#pragma once

#include "headers.hpp"

namespace glfw {

	inline void poll_events() {
		glfwPollEvents();
	}

}
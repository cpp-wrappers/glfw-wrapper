#pragma once

#include "headers.hpp"
#include "error.hpp"

namespace glfw {

	inline bool try_init() {
		return glfwInit();
	}

}
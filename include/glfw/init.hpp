#pragma once

#include "headers.hpp"
#include "error.hpp"

namespace glfw {

	inline glfw::error try_init() {
		return (glfw::error) glfwInit();
	}

}
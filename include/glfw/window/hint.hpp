#pragma once

#include "../function.hpp"

extern "C" GLFW_API void glfwWindowHint(int hint, int value);

namespace glfw {

	struct window_hint {

		window_hint(int hint, int value) {
			glfwWindowHint(hint, value);
		}

		enum {
			no_api = 0,
			client_api = 0x00022001
		};
	};

} // glfw
#pragma once

#include "function.hpp"

extern "C" GLFW_API int glfwGetError(const char** description);

namespace glfw {

	enum class error {
		no                  = 0,
		not_initialized     = 0x00010001,
		no_current_context  = 0x00010002,
		invalid_enum        = 0x00010003,
		invalid_value       = 0x00010004,
		out_of_memory       = 0x00010005,
		api_unavailable     = 0x00010006,
		version_unavailable = 0x00010007,
		platform_error      = 0x00010008,
		format_unavailable  = 0x00010009,
		no_window_context   = 0x0001000A
	};

	inline glfw::error get_error() {
		return (glfw::error) glfwGetError(nullptr);
	}

} // glfw
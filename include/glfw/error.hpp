#pragma once

#include "headers.hpp"

namespace glfw {

	enum class error {
		no = GLFW_NO_ERROR,
		not_initialized = GLFW_NOT_INITIALIZED,
		no_current_context = GLFW_NO_CURRENT_CONTEXT,
		invalid_enum = GLFW_INVALID_ENUM,
		invalid_value = GLFW_INVALID_VALUE,
		out_of_memory = GLFW_OUT_OF_MEMORY,
		api_unavailable = GLFW_API_UNAVAILABLE,
		version_unavailable = GLFW_VERSION_UNAVAILABLE,
		platform_error = GLFW_PLATFORM_ERROR,
		format_unavailable = GLFW_FORMAT_UNAVAILABLE,
		no_window_context = GLFW_NO_WINDOW_CONTEXT
	};

	inline glfw::error get_error() {
		return (glfw::error) glfwGetError(nullptr);
	}

} // glfw
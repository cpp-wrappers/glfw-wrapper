#pragma once

#include "error.hpp"
#include "unexpected_handler.hpp"
#include "function.hpp"

#include <core/span.hpp>
#include <core/c_string.hpp>
#include <core/expected.hpp>

extern "C" GLFW_API const char** glfwGetRequiredInstanceExtensions(uint32* count);

extern "C" GLFW_API int glfwVulkanSupported(void);

namespace glfw {

	inline bool is_vulkan_supported() {
		return glfwVulkanSupported();
	}

	inline expected<span<c_string>, glfw::error>
	try_get_required_instance_extensions() {
		uint32 count;
		const char** result = glfwGetRequiredInstanceExtensions(&count);
		if(result == nullptr) {
			return glfw::error{ glfw::get_error() };
		}
		return span<c_string>{ (c_string*) result, count };
	}

	inline span<c_string> get_required_instance_extensions() {
		auto result = glfw::try_get_required_instance_extensions();
		if(result.is_unexpected()) {
			glfw::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // glfw
#pragma once

#include "handle.hpp"
#include "../function.hpp"

#include <vk/instance/handle.hpp>
#include <vk/surface/handle.hpp>

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

extern "C" GLFW_API int32 glfwCreateWindowSurface(
	handle<vk::instance> instance,
	handle<glfw::window> window,
	const void* allocator,
	handle<vk::surface>* surface
);

namespace glfw {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::instance>>,
		types::are_contain_one_decayed<handle<glfw::window>>
	>::for_types<Args...>
	vk::expected<handle<vk::surface>>
	try_create_window_surface(Args&&... args) {
		auto instance = elements::decayed<handle<vk::instance>>(args...);

		auto window = elements::decayed<handle<glfw::window>>(args...);

		handle<vk::surface> surface;

		vk::result result {
			glfwCreateWindowSurface(
				instance,
				window,
				nullptr,
				&surface
			)
		};

		if(result.error()) {
			return result;
		}

		return surface;
	}

	template<typename... Args>
	handle<vk::surface> create_window_surface(Args&&... args) {
		auto result = glfw::try_create_window_surface(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // glfw
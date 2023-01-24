#pragma once

#if __has_include(<vk/instance.hpp>) && __has_include(<vk/surface.hpp>)

#include "./handle.hpp"
#include "../__internal/function.hpp"

#include <vk/instance.hpp>
#include <vk/surface.hpp>

#include <types.hpp>
#include <tuple.hpp>

extern "C" GLFW_API int32 glfwCreateWindowSurface(
	handle<vk::instance>::underlying_type instance,
	handle<glfw::window>::underlying_type window,
	const void* allocator,
	handle<vk::surface>::underlying_type* surface
);

namespace glfw {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<glfw::window>> == 1
	>
	vk::expected<handle<vk::surface>>
	try_create_window_surface(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<glfw::window> window = tuple{ args... }.template
			get_decayed_same_as<handle<glfw::window>>();

		handle<vk::surface> surface;

		vk::result result {
			glfwCreateWindowSurface(
				instance.underlying(),
				window.underlying(),
				nullptr,
				&surface.underlying()
			)
		};

		if(result.error()) {
			return result;
		}

		return surface;
	}

	template<typename... Args>
	handle<vk::surface> create_window_surface(Args&&... args) {
		vk::expected<handle<vk::surface>> result
			= glfw::try_create_window_surface(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // glfw

inline handle<vk::surface> handle_interface<glfw::window>::
create_surface(handle<vk::instance> instance) {
	return glfw::create_window_surface(
		handle<glfw::window>{ underlying() },
		instance
	);
}

#endif
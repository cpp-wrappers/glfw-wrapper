#pragma once

#include <handle.hpp>
#include <math/vector.hpp>

#if __has_include(<vk/instance.hpp>) && __has_include(<vk/surface.hpp>)
	#include <vk/instance.hpp>
	#include <vk/surface.hpp>
#endif

namespace glfw {

	struct window;

} // glfw

template<>
struct handle_underlying_t<glfw::window> {
	using type = void*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<glfw::window> : handle_interface_base<glfw::window> {
	inline math::vector<double, 2> get_cursor_pos() const;
	inline bool should_close() const;

	#if __has_include(<vk/instance.hpp>)
		inline handle<vk::surface> create_surface(
			handle<vk::instance> instance
		);
	#endif

};

#include "should_close.hpp"
#include "get_cursor_pos.hpp"
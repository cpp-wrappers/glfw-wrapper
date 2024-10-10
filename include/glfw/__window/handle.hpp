#pragma once

#include <handle.hpp>
#include <math/vector.hpp>

#include "../__internal/function.hpp"

extern "C" GLFW_API int glfwGetKey(struct GLFWwindow* window, int key);

#if __has_include(<vk/instance.hpp>) && __has_include(<vk/surface.hpp>)
	#include <vk/instance.hpp>
	#include <vk/surface.hpp>
#endif

#include "../__internal/key.hpp"

namespace glfw {

	struct window;

	using key_callback_t = void(*)(
		glfw::window* window,
		glfw::key::code key,
		int scancode,
		glfw::key::action action,
		glfw::key::modifiers mods
	);

} // glfw

template<>
struct handle_underlying_t<glfw::window> {
	using type = glfw::window*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<glfw::window> : handle_interface_base<glfw::window> {

	inline void show() const;

	inline math::vector<double, 2> get_cursor_pos() const;

	inline math::vector<int, 2> get_size() const;

	inline bool should_close() const;

	#if __has_include(<vk/instance.hpp>)
		inline handle<vk::surface> create_surface(
			handle<vk::instance> instance
		);
	#endif

	glfw::key_callback_t set_key_callback(glfw::key_callback_t callback) const;

	glfw::key::action get_key(glfw::key::code key_code) const {
		return (glfw::key::action) ::glfwGetKey(
			(struct GLFWwindow*) underlying(), (int) key_code
		);
	}

};
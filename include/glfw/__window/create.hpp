#pragma once

#include "handle.hpp"
#include "../__internal/error.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__internal/function.hpp"

#include <c_string.hpp>
#include <expected.hpp>
#include <types.hpp>
#include <tuple.hpp>
#include <body.hpp>

#include <unicode/utf8.hpp>

namespace glfw {

	class width {
		int value_;
	public:
		width(int value) : value_{ value } {}
		explicit operator int () const { return value_; }
	};

	class height {
		int value_;
	public:
		height(int value) : value_{ value } {}
		explicit operator int () const { return value_; }
	};

	struct title : c_string<utf8::unit> {};

}

extern "C" GLFW_API void* glfwCreateWindow(
	int width,
	int height,
	const utf8::unit* title,
	void* monitor,
	void* share
);

namespace glfw::internal {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<glfw::width>.decayed == 1,
		is_same_as<glfw::height>.decayed == 1,
		is_same_as<glfw::title>.decayed <= 1
	>
	expected<handle<glfw::window>, glfw::error>
	try_create_window(Args&&... args) {
		glfw::width width = tuple{ args... }.template
			get<is_same_as<glfw::width>.decayed>();

		glfw::height height = tuple{ args... }.template
			get<is_same_as<glfw::height>.decayed>();

		glfw::title title{ u8""s };
		if constexpr (types<Args...>::template
			count_of<is_same_as<glfw::title>.decayed> == 1
		) {
			title = tuple{ args... }.template
				get<is_same_as<glfw::title>.decayed>();
		}

		glfw::window* result = (glfw::window*) glfwCreateWindow(
			(int) width, (int) height, title.iterator(),
			nullptr, nullptr
		);

		if (result == nullptr) {
			return glfw::get_error();
		}

		return handle<glfw::window>{ result };
	}

	template<typename... Args>
	handle<glfw::window> create_window(Args&&... args) {
		expected<handle<glfw::window>, glfw::error> result
			= glfw::internal::try_create_window(forward<Args>(args)...);
		if (result.is_unexpected()) {
			unexpected_handler(result.get_unexpected());
		}
		return move(result.get_expected());
	}

} // glfw::internal
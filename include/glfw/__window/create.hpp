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

	struct title : c_string_of_unknown_size {};

}

extern "C" GLFW_API void* glfwCreateWindow(
	int width,
	int height,
	const char* title,
	void* monitor,
	void* share
);

namespace glfw::internal {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<glfw::width> == 1,
		count_of_decayed_same_as<glfw::height> == 1,
		count_of_decayed_same_as<glfw::title> <= 1
	>
	expected<handle<glfw::window>, glfw::error>
	try_create_window(Args&&... args) {
		glfw::width width = tuple{ args... }.template
			get_decayed_same_as<glfw::width>();

		glfw::height height = tuple{ args... }.template
			get_decayed_same_as<glfw::height>();

		glfw::title title{ "" };
		if constexpr (types<Args...>::template
			count_of_decayed_same_as<glfw::title> == 1
		) {
			title = tuple{ args... }.template
				get_decayed_same_as<glfw::title>();
		}

		void* result = glfwCreateWindow(
			(int) width, (int) height, title.iterator(),
			nullptr, nullptr
		);

		if(result == nullptr) {
			return glfw::get_error();
		}

		return handle<glfw::window>{ result };
	}

	template<typename... Args>
	handle<glfw::window> create_window(Args&&... args) {
		expected<handle<glfw::window>, glfw::error> result
			= glfw::internal::try_create_window(forward<Args>(args)...);
		if(result.is_unexpected()) {
			unexpected_handler(result.get_unexpected());
		}
		return move(result.get_expected());
	}

} // glfw::internal
#pragma once

#include "handle.hpp"
#include "../error.hpp"
#include "../unexpected_handler.hpp"
#include "../function.hpp"

#include <core/c_string.hpp>
#include <core/expected.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace glfw {

	struct width  { int32 _; };
	struct height { int32 _; };
	struct title : c_string {};

}

extern "C" GLFW_API handle<glfw::window> glfwCreateWindow(
	glfw::width width,
	glfw::height height,
	glfw::title title,
	void* monitor,
	void* share
);

namespace glfw {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<glfw::width>,
		types::are_contain_one_decayed<glfw::height>,
		types::are_may_contain_one_decayed<glfw::title>
		// TODO monitor
	>::for_types<Args...>
	expected<handle<glfw::window>, glfw::error>
	try_create_window(Args&&... args) {
		auto width = elements::decayed_same_as<glfw::width>(args...);
		auto height = elements::decayed_same_as<glfw::height>(args...);
		glfw::title title{};

		if constexpr (
			types::are_contain_decayed<glfw::title>::for_types<Args...>
		) { title = elements::decayed_same_as<glfw::title>(args...); }

		auto result = glfwCreateWindow(
			width,
			height,
			title,
			nullptr,
			nullptr
		);

		if(result.raw() == nullptr) {
			return glfw::get_error();
		}

		return handle<glfw::window>{ result };
	}

	template<typename... Args>
	handle<glfw::window> create_window(Args&&... args) {
		auto result = glfw::try_create_window(forward<Args>(args)...);
		if(result.is_unexpected()) {
			unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // glfw
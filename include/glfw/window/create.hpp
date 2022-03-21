#pragma once

#include "handle.hpp"
#include "../error.hpp"
#include "../default_unexpected_handler.hpp"

#include <core/c_string.hpp>
#include <core/expected.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace glfw {

	struct width : wrapper::of_integer<int32> {};
	struct height : wrapper::of_integer<int32> {};
	struct title : c_string {};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_decayed<glfw::width>,
		types::are_contain_one_decayed<glfw::height>,
		types::are_may_contain_one_decayed<glfw::title>
		// TODO monitor
	>::for_types<Args...>
	expected<handle<glfw::window>, glfw::error>
	try_create_window(Args&&... args) {
		auto width = elements::decayed_same_as<glfw::width>(args...);
		auto height = elements::decayed_same_as<glfw::height>(args...);
		c_string title{};

		if constexpr (types::are_contain_decayed<glfw::title>::for_types<Args...>) {
			title = elements::decayed_same_as<glfw::title>(args...);
		}

		auto result = glfwCreateWindow(
			(int) width,
			(int) height,
			title.begin(),
			(GLFWmonitor*) nullptr,
			(GLFWwindow*) nullptr
		);

		if(result == nullptr) {
			return glfw::get_error();
		}

		return handle<glfw::window>{ result };
	}

	template<typename... Args>
	handle<glfw::window> create_window(Args&&... args) {
		expected<handle<glfw::window>, glfw::error> result = glfw::try_create_window(forward<Args>(args)...);
		if(result.is_unexpected()) {
			default_unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // glfw
#pragma once

#include <core/handle/declaration.hpp>

#include "../headers.hpp"

namespace glfw {

	struct window;

} // glfw

template<>
struct handle<glfw::window> {
	GLFWwindow* m_raw;

	auto& raw() const {
		return m_raw;
	}

	auto& raw() {
		return m_raw;
	}

};

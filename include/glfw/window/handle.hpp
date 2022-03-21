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

	inline bool should_close() const;

};

#include "should_close.hpp"

inline bool handle<glfw::window>::should_close() const {
	return glfw::window_should_close(*this);
}

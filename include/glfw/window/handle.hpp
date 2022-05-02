#pragma once

#include <core/handle.hpp>
#include <math/vector.hpp>

namespace glfw {

	struct window;

} // glfw

template<>
struct handle<glfw::window> {
	void* m_raw;

	auto& raw() const {
		return m_raw;
	}

	auto& raw() {
		return m_raw;
	}

	inline math::vector<double, 2> get_cursor_pos() const;

	inline bool should_close() const;
};

#include "should_close.hpp"
#include "get_cursor_pos.hpp"
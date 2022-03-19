#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include <core/handle/guarded_declaration.hpp>

template<>
struct guarded_handle<glfw::window> {
	handle<glfw::window> m_handle;

	~guarded_handle() {
		glfw::destroy_window(m_handle);
		m_handle.raw() = nullptr;
	}

};

#include "create.hpp"

namespace glfw {

	template<typename... Args>
	guarded_handle<glfw::window>
	create_guarded_window(Args&&... args) {
		return { glfw::create_window(forward<Args>(args)...) };
	}

} // glfw
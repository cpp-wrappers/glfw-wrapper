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

	auto& handle() const { return m_handle; }
	auto& handle() { return m_handle; }

	auto& raw() const { return handle().raw(); }
	auto& raw() { return handle().raw(); }

	bool should_close() const { return handle().should_close(); }
};

#include "create.hpp"

namespace glfw {

	template<typename... Args>
	guarded_handle<glfw::window>
	create_guarded_window(Args&&... args) {
		return { glfw::create_window(forward<Args>(args)...) };
	}

} // glfw
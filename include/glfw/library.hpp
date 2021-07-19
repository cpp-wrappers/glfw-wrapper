#pragma once

#include "error.hpp"
#include "window.hpp"
#include <optional>
#include <tl/expected.hpp>

namespace glfw {

class window;

namespace internal {
	int init() noexcept;
	void terminate() noexcept;
	void poll_events() noexcept;
}

inline struct library_t {
	library_t() {
		if(!internal::init()) {
			throw glfw::error{};
		}
	}

	tl::expected<std::reference_wrapper<glfw::window>, glfw::error>
	try_create_window(unsigned width, unsigned height, const char* title) const noexcept;

	glfw::window& create_window(unsigned width, unsigned height, const char* title) const {
		auto result = try_create_window(width, height, title);
		if(!result) {
			throw glfw::error{};
		}
		return result.value();
	}

	void try_poll_events() const noexcept {

	}

	~library_t() {
		internal::terminate();
	}

} library;

}
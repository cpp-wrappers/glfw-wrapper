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

	tl::expected<void, glfw::error>
	try_poll_events() const noexcept {
		internal::poll_events();

		auto code = get_error_code();
		if(code != 0) {
			return tl::unexpected{ glfw::error{} };
		}

		return {};
	}

	void poll_events() const {
		auto result = try_poll_events();
		if(!result) {
			throw result.error();
		}
	}

	~library_t() {
		//internal::terminate();
	}

} library;

}
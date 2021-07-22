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
	void window_hint(int hint, int value) noexcept;
}

template<typename T>
struct window_hint {
	int code;
};

namespace hints {
	inline constexpr window_hint<bool> doublebuffer{ 0x00021010 };
	inline constexpr window_hint<int> context_version_major{ 0x00022002 };
	inline constexpr window_hint<int> context_version_minor{ 0x00022003 };
	inline constexpr window_hint<bool> opengl_debug_context{ 0x00022007 };
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
			throw result.error();
		}
		return result.value();
	}

	tl::expected<void, glfw::error>
	try_poll_events() const noexcept {
		internal::poll_events();

		auto error = get_error();
		if(error.code != 0) {
			return tl::unexpected{ glfw::error{ error.description } };
		}

		return {};
	}

	void poll_events() const {
		auto result = try_poll_events();
		if(!result) {
			throw result.error();
		}
	}

	template<typename T>
	void window_hint(window_hint<T> hint, T val) {
		internal::window_hint(hint.code, val);
	}

	~library_t() {
		internal::terminate();
	}

} library;

}
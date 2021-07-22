#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <functional>

#include "key.hpp"
#include "unified_math/vec2.hpp"
#include "unified_math/to.hpp"
#include <memory>

namespace glfw {

class window {
	friend class library_t;
	window() = default;
public:

	void make_context_current();
	bool should_close();
	void swap_buffers();
	void pos(int x, int y);
	void pos(uni::vec2i auto pos) {
		pos(get<0>(pos), get<1>(pos));
	}

	void cursor_pos(double x, double y);
	void cursor_pos(uni::vec2d auto pos) {
		pos(get<0>(pos), get<1>(pos));
	}

	std::pair<unsigned, unsigned> framebuffer_size();
	std::pair<unsigned, unsigned> size();

	template<uni::any_vec2 V>
	V framebuffer_size() {
		auto s = framebuffer_size();
		return { get<0>(s), get<1>(s) };
	}

	explicit operator bool() { return !should_close(); }

	using pos_callback = void(*)(glfw::window* w, int x, int y);
	void set_pos_callback(pos_callback callback) const noexcept;

	using size_callback = void(*)(glfw::window* w, int width, int height);
	void set_size_callback(size_callback callback) const noexcept;

	using close_callback = void(*)(glfw::window* w);
	void set_close_callback(close_callback callback) const noexcept;

	using refresh_callback = void(*)(glfw::window* w);
	void set_refresh_callback(refresh_callback callback) const noexcept;

	using focus_callback = void(*)(glfw::window* w, int focused);
	void set_focus_callback(focus_callback callback) const noexcept;

	using iconify_callback = void(*)(glfw::window* w, int iconified);
	void set_iconify_callback(iconify_callback callback) const noexcept;

	using window_maximize_callback = void(*)(glfw::window* w, int maximized);
	void set_maximize_callback(window_maximize_callback callback) const noexcept;

	using framebuffer_size_callback = void(*)(glfw::window* w, int width, int height);
	void set_framebuffer_size_callback(framebuffer_size_callback callback) const noexcept;

	using content_scale_callback = void(*)(glfw::window* w, float scale_x, float scale_y);
	void set_content_cale_callback(content_scale_callback callback) const noexcept;

	using mouse_button_callback = void(*)(glfw::window* w, glfw::key::code button, glfw::key::action action, glfw::key::modifier mods);
	void set_mouse_button_callback(mouse_button_callback callback) const noexcept;

	using cursor_pos_callback = void(*)(glfw::window* w, double x, double y);
	void set_cursor_pos_callback(cursor_pos_callback callback) const noexcept;

	using cursor_enter_callback = void(*)(glfw::window* w, int entered);
	void set_cursor_enter_callback(cursor_enter_callback callback) const noexcept;

	using scroll_callback = void(*)(glfw::window* w, double offset_x, double offset_y);
	void set_scroll_callback(scroll_callback callback) const noexcept;

	using key_callback = void(*)(glfw::window* w, glfw::key::code code, int scancode, glfw::key::action action, glfw::key::modifier modifiers);
	void set_key_callback(key_callback callback) const noexcept;

	using char_callback = void(*)(glfw::window* w, unsigned codepoint);
	void set_char_callback(char_callback callback) const noexcept;

	using drop_callback = void(*)(glfw::window* w, int paths_count, const char* paths[]);
	void set_drop_callback(drop_callback callback) const noexcept;
};
}

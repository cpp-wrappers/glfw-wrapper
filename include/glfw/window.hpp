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
private:

	void make_context_current();
	bool should_close();
	void swap_buffers();
	void position(int x, int y);
	void position(uni::vec2i auto pos) {
		position(get<0>(pos), get<1>(pos));
	}

	std::pair<unsigned, unsigned> framebuffer_size();

	template<uni::vec2u V>
	V framebuffer_size() {
		return { framebuffer_size() };
	}

	explicit operator bool() { return !should_close(); }


	/*void set_window_pos_callback(window_pos_callback<> callback);
	template<uni::vec2i Vec>
	void set_window_pos_callback(window_pos_callback<Vec> callback) {
		set_window_pos_callback<>([&](auto pos){
			callback(uni::to(pos));
		});
	}
	void set_window_size_callback(window_size_callback callback);
	void set_close_callback(window_close_callback callback);
	void set_refresh_callback(window_refresh_callback callback);
	void set_focus_callback(window_focus_callback callback);
	void set_iconify_callback(window_iconify_callback callback);
	void set_maximize_callback(window_maximize_callback callback);
	void set_framebuffer_size_callback(framebuffer_size_callback callback);
	void set_window_content_cale_callback(window_content_scale_callback callback);
	void set_mouse_button_callback(mouse_button_callback callback);
	void set_cursor_pos_callback(cursor_pos_callback callback);
	void set_cursor_enter_callback(cursor_enter_callback callback);
	void set_croll_callback(scroll_callback callback);
	void set_key_callback(key_callback callback);
	void set_char_callback(char_callback callback);
	void set_drop_callback(drop_callback callback);*/
};
}

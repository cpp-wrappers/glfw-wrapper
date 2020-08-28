#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <functional>

#include "key.hpp"
#include "unified_math/vec.hpp"

namespace glfw {

class window {
	using window_pos_callback = std::function<void(uni::vec2i)>;
	using window_size_callback = std::function<void(uni::vec2ui)>;
	using window_close_callback = std::function<void()>;
	using window_refresh_callback = std::function<void()>;
	using window_focus_callback = std::function<void(bool)>;
	using window_iconify_callback = std::function<void(bool)>;
	using window_maximize_callback = std::function<void(bool)>;
	using framebuffer_size_callback = std::function< void(uni::vec2ui)>;
	using window_content_scale_callback = std::function<void(uni::vec2f)>;
	using mouse_button_callback = std::function<void(mouse_button button, mouse_button::action action, const std::vector<key::modifier>& mods)>;
	using cursor_pos_callback = std::function<void(uni::vec2d)>;
	using cursor_enter_callback = std::function<void(bool entered)>;
	using scroll_callback = std::function<void(uni::vec2d)>;
	using key_callback = std::function<void(glfw::key key, int scancode, key::action action, const std::vector<key::modifier>& mods)>;
	using char_callback = std::function<void(unsigned codepoint)>;
	//using char_mods_callback = std::function<void(uint codepoint, int mods)>;
	using drop_callback = std::function<void(const std::vector<std::filesystem::path>&)>;
	//using joystick_callback = std::function<void(int jid, int event)>;

	struct {
		window_pos_callback win_pos;
		window_size_callback win_size;
		window_close_callback win_close;
		window_refresh_callback win_refresh;
		window_focus_callback win_focus;
		window_iconify_callback win_icon;
		window_maximize_callback win_maximize;
		framebuffer_size_callback framebuffer_size;
		window_content_scale_callback win_content_scale;
		mouse_button_callback mouse_button;
		cursor_pos_callback cursor_pos;
		cursor_enter_callback cursor_enter;
		scroll_callback scroll;
		key_callback key;
		char_callback unicode_char;
		//char_mods_callback char_mods;
		drop_callback drop;
		//monitor_callback monitor;
		//joystick_callback joystick;
	} callbacks;
private: void* handle;
public:
	class hints;

	struct hint {
		friend hints;
		unsigned code, value;
	private:
		void apply();
	};

	class hints : std::vector<hint> {
		friend window;
		void apply() { for (auto& h : *this) h.apply(); }
	public:
		hints& gl_debug_context();
		hints& context_version(unsigned major, unsigned minor);
		hints& gl_core_profile();
	};

	window(uni::vec2ui size, std::string title, window::hints hints = {});
	window(window&& r);
	~window();

	void make_context_current();
	bool should_close();
	void swap_buffers();
	void position(uni::vec2i position);
	uni::vec2ui framebuffer_size();

	operator bool() {
		return !should_close();
	}

	void set_window_pos_callback(window_pos_callback callback);
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
	void set_drop_callback(drop_callback callback);
};
}

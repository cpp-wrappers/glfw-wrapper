#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <functional>
#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "pressable.hpp"
#include "monitor.hpp"

namespace glfw {

class window {
	using window_pos_callback = std::function<void(int x, int y)>;
	using window_size_callback = std::function<void(int width, int height)>;
	using window_close_callback = std::function<void()>;
	using window_refresh_callback = std::function<void()>;
	using window_focus_callback = std::function<void(bool)>;
	using window_iconify_callback = std::function<void(bool)>;
	using window_maximize_callback = std::function<void(bool)>;
	using framebuffer_size_callback = std::function< void(int width, int height)>;	
	using window_content_scale_callback = std::function<void(float xscale, float yscale)>;
	using mouse_button_callback = std::function<void(mouse_button button, mouse_button::action action, const std::vector<key::modifier>& mods)>;
	using cursor_pos_callback = std::function<void(double xpos, double ypos)>;
	using cursor_enter_callback = std::function<void(bool entered)>;
	using scroll_callback = std::function<void(double xoffset, double yoffset)>;
	using key_callback = std::function<void(glfw::key key, int scancode, key::action action, const std::vector<key::modifier>& mods)>;
	using char_callback = std::function<void(uint codepoint)>;
	//using char_mods_callback = std::function<void(uint codepoint, int mods)>;
	using drop_callback = std::function<void(const std::vector<std::filesystem::path>&)>;
	//using joystick_callback = std::function<void(int jid, int event)>;

public:
	struct {
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
			monitor_callback monitor;
			joystick_callback joystick;
		} callbacks_table;
	} internal;
private: GLFWwindow* raw;
public:

	class hints {
		hints() {} // Fake namespace

	public:
		class hint {
		protected:
			uint code;
			uint value;
		public:
			hint(uint code, uint value) : code{ code }, value{ value }{}
			void set_hint() {
				glfwWindowHint(code, value);
			}
		};

		class bool_hint : public hint {
		protected:
			bool_hint(uint code, bool value) : hint(code, value) {}
		};

		class opengl_debug_context : public bool_hint {
		public:
			opengl_debug_context(bool value) : bool_hint(GLFW_OPENGL_DEBUG_CONTEXT, value) {}
		};
	};

	window(
		uint width,
		uint height,
		std::string title,
		std::initializer_list<window::hints::hint> hints = {}
	) {
		if(!glfwInit()) throw std::runtime_error("error while initializing glfw");

		for (auto hint : hints)
			hint.set_hint();
		
		if(!(raw = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)))
			throw std::runtime_error("error while creating glfw window");
		glfwSetWindowUserPointer(raw, this);
	}

	window(window&& r) = default;

	~window() {
		if(raw == nullptr) return;
		glfwDestroyWindow(raw);
		raw = nullptr;
	}

	void make_context_current() {
		glfwMakeContextCurrent(raw);
	}

	bool should_close() {
		return glfwWindowShouldClose(raw);
	}

	void swap_buffers() {
		glfwSwapBuffers(raw);
	}
	
	void swap_interval(int interval) {
		glfwSwapInterval(interval);
	}

public:
	void set_window_pos_callback(window_pos_callback cb) {
		internal.callbacks_table.win_pos = cb;
		glfwSetWindowPosCallback(raw, [](GLFWwindow* w, int x, int y) {
			((glfw::window*)glfwGetWindowUserPointer(w))
				->internal.callbacks_table.win_pos(x, y);
		});
	}

	void set_window_size_callback(window_size_callback cb) {
		internal.callbacks_table.win_size = cb;
		glfwSetWindowSizeCallback(raw, [](GLFWwindow* raw_, int w, int h) {
			((glfw::window*)glfwGetWindowUserPointer(raw_))
				->internal.callbacks_table.win_size(w, h);
		});
	}

	void set_close_callback(window_close_callback cb) {
		internal.callbacks_table.win_close = cb;
		glfwSetWindowCloseCallback(raw, [](GLFWwindow* raw_) {
			((glfw::window*)glfwGetWindowUserPointer(raw_))
				->internal.callbacks_table.win_close();
		});
	}

	void set_refresh_callback(window_refresh_callback cb) {
		internal.callbacks_table.win_refresh = cb;
		glfwSetWindowRefreshCallback(raw, [](GLFWwindow* raw_) {
			((glfw::window*)glfwGetWindowUserPointer(raw_))
				->internal.callbacks_table.win_refresh();
		});
	}

	void set_focus_callback(window_focus_callback cb) {
		internal.callbacks_table.win_focus = cb;
		glfwSetWindowFocusCallback(raw, [](GLFWwindow* raw_, int v) {
			((glfw::window*)glfwGetWindowUserPointer(raw_))
				->internal.callbacks_table.win_focus(v);
		});
	}

	void set_iconify_callback(window_iconify_callback cb) {
		internal.callbacks_table.win_icon = cb;
		glfwSetWindowIconifyCallback(raw, [](GLFWwindow* raw_, int v) {
			((glfw::window*)glfwGetWindowUserPointer(raw_))
				->internal.callbacks_table.win_icon(v);
		});
	}

	void set_maximize_callback(window_maximize_callback cb) {
		internal.callbacks_table.win_maximize = cb;
		glfwSetWindowMaximizeCallback(raw, [](GLFWwindow* raw_, int v) {
			((glfw::window*)glfwGetWindowUserPointer(raw_))
				->internal.callbacks_table.win_maximize(v);
		});
	}

	void set_framebuffer_size_callback(framebuffer_size_callback cb) {
		internal.callbacks_table.framebuffer_size = cb;
		glfwSetFramebufferSizeCallback(raw, [](GLFWwindow* w_, int w, int h) {
			((glfw::window*)glfwGetWindowUserPointer(w_))
				->internal.callbacks_table.framebuffer_size(w, h);
		});
	}

	void set_window_content_cale_callback(window_content_scale_callback cb) {
		internal.callbacks_table.win_content_scale = cb;
		glfwSetWindowContentScaleCallback(raw, [](GLFWwindow* w_, float xs, float ys) {
			((glfw::window*)glfwGetWindowUserPointer(w_))
				->internal.callbacks_table.win_content_scale(xs, ys);
		});
	}

	void set_mouse_button_callback(mouse_button_callback cb) {
		internal.callbacks_table.mouse_button = cb;
		glfwSetMouseButtonCallback(raw, [](GLFWwindow* w, int mb, int action, int mods) {
			std::vector<key::modifier> v;
			for(uint i = 0; i < sizeof(uint); i++ ) {
				unsigned mask = 1 << i;
				if(mods & mask) v.push_back((key::modifier)mask);
			}

			((glfw::window*)glfwGetWindowUserPointer(w_))
				->internal.callbacks_table.mouse_button(mouse_button{mb}, (mouse_button::action)action, v);
		});
	}

	void set_cursor_pos_callback(cursor_pos_callback cb) {
		internal.callbacks_table.cursor_pos = cb;		
		glfwSetCursorPosCallback(raw, [](GLFWwindow* w_, double x, double y) {
			((glfw::window*)glfwGetWindowUserPointer(w_))
				->internal.callbacks_table.cursor_pos(x, y);
		});
	}

	void set_cursor_enter_callback(cursor_enter_callback cb) {
		internal.callbacks_table.cursor_enter = cb;
		glfwSetCursorEnterCallback(raw, [](GLFWwindow* w_, int entered) {
			((glfw::window*)glfwGetWindowUserPointer(w_))
				->internal.callbacks_table.cursor_enter(entered);
		});
	}

	void set_croll_callback(scroll_callback cb) {
		internal.callbacks_table.scroll = cb;
		glfwSetScrollCallback(raw, [](GLFWwindow* w_, double xo, double yo) {
			((glfw::window*)glfwGetWindowUserPointer(w_))
				->internal.callbacks_table.scroll(xo, yo);
		});
	}

	void set_key_callback(key_callback cb) {
		internal.callbacks_table.key = cb;

		glfwSetKeyCallback(raw, [](GLFWwindow* w, int k, int sc, int a, int mods) {
			std::vector<key::modifier> v;
			for(uint i = 0; i < sizeof(uint); i++ ) {
				unsigned mask = 1 << i;
				if(mods & mask) v.push_back((key::modifier)mask);
			}

			((glfw::window*)glfwGetWindowUserPointer(w))
				->internal.callbacks_table.key(glfw::key{k}, sc, (glfw::key::action)a, v);
		});
	}
	
	void set_char_callback(char_callback cb) {
		internal.callbacks_table.unicode_char = cb;
		glfwSetCharCallback(raw, [](GLFWwindow* w_, uint c) {
			((glfw::window*)glfwGetWindowUserPointer(w_))
				->internal.callbacks_table.unicode_char(c);
		});
	}

	// Deprecated, will be removed in 4.0 (yay)
	/*void set_char_mods_callback(char_mods_callback cb) {
		internal.callbacks_table.char_mods = cb;
		glfwSetCharModsCallback(raw, [](GLFWwindow* w_, uint c, int mods) {
			
		});
	}*/

	void set_drop_callback(drop_callback cb) {
		internal.callbacks_table.drop = cb;
		glfwSetDropCallback(raw, [](GLFWwindow* w, int c, const char** p) {
			std::vector<std::filesystem::path> v(c);

			for(int i = 0; i < c; i++)
				v.emplace_back(std::string{p[i]});

			((glfw::window*)glfwGetWindowUserPointer(w))
				->internal.callbacks_table.drop(v);
		});
	}

	template<class Vec2>
	Vec2 framebuffer_size() {
		int w;
		int h;
		glfwGetFramebufferSize(raw, &w, &h);
		return {w, h};
	}
};
}

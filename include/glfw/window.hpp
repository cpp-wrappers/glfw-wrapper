#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <functional>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "key.hpp"

namespace glfw {

class window {
	using error_callback = void(int code, std::string desc);
	using window_pos_callback = void(int x, int y);
	using window_size_callback = void(int width, int height);
	using window_close_callback = void();
	using window_refresh_callback = void();
	using window_focus_callback = void(bool);
	using window_iconify_callback = void(bool);
	using window_maximize_callback = void(bool);
	using framebuffer_size_callback = void(int width, int height);
	using window_content_scale_callback = void(float xscale, float yscale);
	using mouse_button_callback = void(int button, int action, int mods);
	using cursor_pos_callback = void(double xpos, double ypos);
	using cursor_enter_callback = void(bool);
	using scroll_callback = void(double xoffset, double yoffset);
	using key_callback = void(glfw::key key, int scancode, key::action action, const std::vector<key::modifier>& mods);
	using char_callback = void(uint codepoint);
	using char_mods_callback = void(uint codepoint, int mods);
	using drop_callback = void(const std::vector<std::filesystem::path>&);
	using monitor_callback = void(int event);
	using joystick_callback = void(int jid, int event);

public:
	struct {
		struct {
			std::function<error_callback> error;
			std::function<window_pos_callback> win_pos;
			std::function<window_size_callback> win_size;
			std::function<window_close_callback> win_close;
			std::function<window_refresh_callback> win_refresh;
			std::function<window_focus_callback> win_focus;
			std::function<window_iconify_callback> win_icon;
			std::function<window_maximize_callback> win_maximize;
			std::function<framebuffer_size_callback> framebuffer_size;
			std::function<window_content_scale_callback> win_content_scale;
			std::function<mouse_button_callback> mouse_button;
			std::function<cursor_pos_callback> cursor_pos;
			std::function<cursor_enter_callback> cursor_enter;
			std::function<scroll_callback> scroll;
			std::function<key_callback> key;
			std::function<char_callback> unicode_char;
			std::function<char_mods_callback> char_mods;
			std::function<drop_callback> drop;
			std::function<monitor_callback> monitor;
			std::function<joystick_callback> joystick;
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
		std::initializer_list<window::hints::hint> hints
	) {
		glfwInit();

		for (auto hint : hints)
			hint.set_hint();
		
		glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(raw, this);
	}

	window(window&& r) = default;

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
	void set_drop_callback(drop_callback cb) {
		internal.callbacks_table.drop = cb;
		glfwSetDropCallback(raw, [](GLFWwindow* w, int c, const char** p) {
			std::vector<std::filesystem::path> v(c);

			for(int i = 0; i < c; i++)
				v.emplace_back(std::string{p[i]});

			auto w_ = (glfw::window*)glfwGetWindowUserPointer(w);
			w_->internal.callbacks_table.drop(v);
		});
	}

	void set_key_callback(key_callback cb) {
		internal.callbacks_table.key = cb;

		glfwSetKeyCallback(raw, [](GLFWwindow* w, int k, int sc, int a, int mods) {
			auto w_ = (glfw::window*)glfwGetWindowUserPointer(w);

			std::vector<key::modifier> v;
			for(uint i = 0; i < sizeof(uint); i++ ) {
				unsigned mask = 1 << i;
				if(mods & mask) v.push_back((key::modifier)mask);
			}

			w_->internal.callbacks_table.key(glfw::key{k}, sc, (glfw::key::action)a, v);
		});
	}

	template<class Vec2>
	Vec2 framebuffer_size() {
		int w;
		int h;
		glfwFramebufferSize();
		return {w, h};
	}
};
}

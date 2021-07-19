#include <utility>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "../include/glfw/window.hpp"
#include <assert.h>

using namespace glfw;

void window::hint::apply() {
	glfwWindowHint(code, value);
}

window::hints& window::hints::gl_debug_context() {
	emplace_back(GLFW_OPENGL_DEBUG_CONTEXT, true);
	return *this;
}

window::hints& window::hints::context_version(unsigned major, unsigned minor) {
	emplace_back(GLFW_CONTEXT_VERSION_MAJOR, major);
	emplace_back(GLFW_CONTEXT_VERSION_MINOR, minor);
	return *this;
}

window::hints& window::hints::gl_core_profile() {
	emplace_back(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	return *this;
}

window::window(unsigned width, unsigned height, std::string title, window::hints hints) {
	if(!glfwInit()) throw std::runtime_error("error while initializing glfw");
	glfwDefaultWindowHints();
	hints.apply();
		
	if(!(handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)))
		throw std::runtime_error("error while creating glfw window");
	glfwSetWindowUserPointer((GLFWwindow*)handle, this);
}

window::window(window&& r) {
	glfwSetWindowUserPointer(
		(GLFWwindow*)(std::exchange(r.handle, nullptr)),
		this
	);
}

window::~window() {
	if(handle) {
		glfwDestroyWindow((GLFWwindow*)std::exchange(handle, nullptr));    
	}
}

void window::make_context_current() { glfwMakeContextCurrent((GLFWwindow*)handle); }
bool window::should_close() { return glfwWindowShouldClose((GLFWwindow*)handle); }
void window::swap_buffers() { glfwSwapBuffers((GLFWwindow*)handle); }

void window::position(int x, int y) {
	glfwSetWindowPos((GLFWwindow*)handle, x, y);
}

std::pair<unsigned, unsigned> window::framebuffer_size() {
	int w, h; glfwGetFramebufferSize((GLFWwindow*)handle, &w, &h);
	assert(w >= 0 and h >= 0);
	return {(unsigned)w, (unsigned)h};
}

static glfw::window* get_window(GLFWwindow* raw) {
	return ((glfw::window*)glfwGetWindowUserPointer(raw));
}

void window::set_window_pos_callback(window_pos_callback<> cb) {
	callbacks.win_pos = cb;
	glfwSetWindowPosCallback((GLFWwindow*)handle, [](GLFWwindow* w, int x, int y) {
		get_window(w)->callbacks.win_pos({x, y});
	});
}

void window::set_window_size_callback(window_size_callback cb) {
	callbacks.win_size = cb;
	glfwSetWindowSizeCallback((GLFWwindow*)handle, [](GLFWwindow* raw, int w, int h) {
		assert(w >= 0 and h >= 0);
		get_window(raw)->callbacks.win_size((unsigned)w, (unsigned)h);
	});
}

void window::set_close_callback(window_close_callback cb) {
	callbacks.win_close = cb;
	glfwSetWindowCloseCallback((GLFWwindow*)handle, [](GLFWwindow* raw) {
		get_window(raw)->callbacks.win_close();
	});
}

void window::set_refresh_callback(window_refresh_callback cb) {
	callbacks.win_refresh = cb;
	glfwSetWindowRefreshCallback((GLFWwindow*)handle, [](GLFWwindow* raw) {
		get_window(raw)->callbacks.win_refresh();
	});
}

void window::set_focus_callback(window_focus_callback cb) {
	callbacks.win_focus = cb;
	glfwSetWindowFocusCallback((GLFWwindow*)handle, [](GLFWwindow* raw, int v) {
		get_window(raw)->callbacks.win_focus(v);
	});
}


void window::set_iconify_callback(window_iconify_callback cb) {
	callbacks.win_icon = cb;
	glfwSetWindowIconifyCallback((GLFWwindow*)handle, [](GLFWwindow* raw, int v) {
		get_window(raw)->callbacks.win_icon(v);
	});
}

void window::set_maximize_callback(window_maximize_callback cb) {
	callbacks.win_maximize = cb;
	glfwSetWindowMaximizeCallback((GLFWwindow*)handle, [](GLFWwindow* raw, int v) {
		get_window(raw)->callbacks.win_maximize(v);
	});
}


void window::set_framebuffer_size_callback(framebuffer_size_callback cb) {
	callbacks.framebuffer_size = cb;
	glfwSetFramebufferSizeCallback((GLFWwindow*)handle, [](GLFWwindow* raw, int w, int h) {
		assert(w >= 0 and h >= 0);
		get_window(raw)->callbacks.framebuffer_size((unsigned)w, (unsigned)h);
	});
}

void window::set_window_content_cale_callback(window_content_scale_callback cb) {
	callbacks.win_content_scale = cb;
	glfwSetWindowContentScaleCallback((GLFWwindow*)handle, [](GLFWwindow* w_, float xs, float ys) {
		get_window(w_)->callbacks.win_content_scale(xs, ys);
	});
}

void window::set_mouse_button_callback(mouse_button_callback cb) {
	callbacks.mouse_button = cb;
	glfwSetMouseButtonCallback((GLFWwindow*)handle, [](GLFWwindow* raw, int mb, int action, int mods) {
		std::vector<key::modifier> v;
		for(unsigned i = 0; i < sizeof(unsigned); i++ ) {
			unsigned mask = 1 << i;
			if(mods & mask) v.push_back((key::modifier)mask);
		}

		get_window(raw)->callbacks.mouse_button(mouse_button{mb}, (mouse_button::action)action, v);
	});
}

void window::set_cursor_pos_callback(cursor_pos_callback cb) {
	callbacks.cursor_pos = cb;
	glfwSetCursorPosCallback((GLFWwindow*)handle, [](GLFWwindow* raw, double x, double y) {
		get_window(raw)->callbacks.cursor_pos(x, y);
	});
}

void window::set_cursor_enter_callback(cursor_enter_callback cb) {
	callbacks.cursor_enter = cb;
	glfwSetCursorEnterCallback((GLFWwindow*)handle, [](GLFWwindow* raw, int entered) {
		get_window(raw)->callbacks.cursor_enter(entered);
	});
}


void window::set_croll_callback(scroll_callback cb) {
	callbacks.scroll = cb;
	glfwSetScrollCallback((GLFWwindow*)handle, [](GLFWwindow* raw, double xo, double yo) {
		get_window(raw)->callbacks.scroll(xo, yo);
	});
}

void window::set_key_callback(key_callback cb) {
	callbacks.key = cb;

	glfwSetKeyCallback((GLFWwindow*)handle, [](GLFWwindow* raw, int k, int sc, int a, int mods) {
		std::vector<key::modifier> v;
		for(unsigned i = 0; i < sizeof(unsigned); i++ ) {
			unsigned mask = 1 << i;
			if(mods & mask) v.push_back((key::modifier)mask);
		}
		get_window(raw)->callbacks.key(glfw::key{k}, sc, (glfw::key::action)a, v);
	});
}

void window::set_char_callback(char_callback cb) {
	callbacks.unicode_char = cb;
	glfwSetCharCallback((GLFWwindow*)handle, [](GLFWwindow* raw, unsigned c) {
		get_window(raw)->callbacks.unicode_char(c);
	});
}

void window::set_drop_callback(drop_callback cb) {
	callbacks.drop = cb;
	glfwSetDropCallback((GLFWwindow*)handle, [](GLFWwindow* raw, int c, const char** p) {
		std::vector<std::filesystem::path> v(c);

		for(int i = 0; i < c; i++)
			v.emplace_back(std::string{p[i]});

		get_window(raw)->callbacks.drop(v);
	});
}
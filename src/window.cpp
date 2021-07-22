#include <GLFW/glfw3.h>
#include <utility>
#include "glfw/window.hpp"
#include "include.hpp"
#include <assert.h>

namespace glfw {

void window::make_context_current() { glfwMakeContextCurrent((GLFWwindow*)this); }
bool window::should_close() { return glfwWindowShouldClose((GLFWwindow*)this); }
void window::swap_buffers() { glfwSwapBuffers((GLFWwindow*)this); }

void window::pos(int x, int y) {
	glfwSetWindowPos((GLFWwindow*)this, x, y);
}

void window::cursor_pos(double x, double y) {
	glfwSetCursorPos((GLFWwindow*)this, x, y);
}

std::pair<unsigned, unsigned> window::framebuffer_size() {
	int w, h; glfwGetFramebufferSize((GLFWwindow*)this, &w, &h);
	assert(w >= 0 and h >= 0);
	return {(unsigned)w, (unsigned)h};
}

std::pair<unsigned, unsigned> window::size() {
	int w, h; glfwGetWindowSize((GLFWwindow*)this, &w, &h);
	assert(w >= 0 and h >= 0);
	return {(unsigned)w, (unsigned)h};
}

void window::set_pos_callback(pos_callback callback) const noexcept {
	glfwSetWindowPosCallback((GLFWwindow*)this, (GLFWwindowposfun) callback);
}

void window::set_size_callback(size_callback callback) const noexcept {
	glfwSetWindowSizeCallback((GLFWwindow*)this, (GLFWwindowsizefun) callback);
}

void window::set_close_callback(close_callback callback) const noexcept {
	glfwSetWindowCloseCallback((GLFWwindow*)this, (GLFWwindowclosefun) callback);
}

void window::set_refresh_callback(refresh_callback callback) const noexcept {
	glfwSetWindowRefreshCallback((GLFWwindow*)this, (GLFWwindowrefreshfun) callback);
}

void window::set_focus_callback(focus_callback callback) const noexcept {
	glfwSetWindowFocusCallback((GLFWwindow*)this, (GLFWwindowfocusfun) callback);
}

void window::set_iconify_callback(iconify_callback callback) const noexcept {
	glfwSetWindowIconifyCallback((GLFWwindow*)this, (GLFWwindowiconifyfun) callback);
}

void window::set_maximize_callback(window_maximize_callback callback) const noexcept {
	glfwSetWindowMaximizeCallback((GLFWwindow*)this, (GLFWwindowmaximizefun) callback);
}

void window::set_framebuffer_size_callback(framebuffer_size_callback callback) const noexcept {
	glfwSetFramebufferSizeCallback((GLFWwindow*)this, (GLFWframebuffersizefun) callback);
}

void window::set_content_cale_callback(content_scale_callback callback) const noexcept {
	glfwSetWindowContentScaleCallback((GLFWwindow*)this, (GLFWwindowcontentscalefun) callback);
}

void window::set_mouse_button_callback(mouse_button_callback callback) const noexcept {
	glfwSetMouseButtonCallback((GLFWwindow*)this, (GLFWmousebuttonfun) callback);
}

void window::set_cursor_pos_callback(cursor_pos_callback callback) const noexcept {
	glfwSetCursorPosCallback((GLFWwindow*)this, (GLFWcursorposfun) callback);
}

void window::set_cursor_enter_callback(cursor_enter_callback callback) const noexcept {
	glfwSetCursorEnterCallback((GLFWwindow*)this, (GLFWcursorenterfun) callback);
}

void window::set_scroll_callback(scroll_callback callback) const noexcept {
	glfwSetScrollCallback((GLFWwindow*)this, (GLFWscrollfun) callback);
}

void window::set_key_callback(key_callback callback) const noexcept {
	glfwSetKeyCallback((GLFWwindow*)this, (GLFWkeyfun) callback);
}

void window::set_char_callback(char_callback callback) const noexcept {
	glfwSetCharCallback((GLFWwindow*)this, (GLFWcharfun) callback);
}

void window::set_drop_callback(drop_callback callback) const noexcept {
	glfwSetDropCallback((GLFWwindow*)this, (GLFWdropfun) callback);
}

}
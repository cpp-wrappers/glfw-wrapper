#if 0
bash build.sh
if ! $CXX \
	--config ./compile_flags.txt \
	-g \
	-fsanitize=address \
	-fsanitize=undefined \
	-Lbuild \
	-o build/window \
	demo/window.cpp \
	-lglfw-wrapper \
	-lglfw
then exit 1
fi
build/window
exit
#endif

#include "glfw/library.hpp"
#include <iostream>

int main() {
	glfw::window& w = glfw::library.create_window(800, 600, "Window");

	w.set_pos_callback([](glfw::window* _, int x, int y) {
		std::cout << "pos: x = " << x << ", y = " << y << std::endl;
	});

	w.set_size_callback([](glfw::window* _, int w, int h) {
		std::cout << "size: w = " << w << ", h = " << h << std::endl;
	});

	w.set_framebuffer_size_callback([](glfw::window* _, int w, int h) {
		std::cout << "framebuffer size: w = " << w << ", h = " << h << std::endl;
	});

	w.set_focus_callback([](glfw::window* w, int focused) {
		std::cout << "focus: " << bool(focused) << std::endl;
	});

	w.set_maximize_callback([](glfw::window* w, int maximized) {
		std::cout << "maximized: " << bool(maximized) << std::endl;
	});

	w.set_mouse_button_callback([](glfw::window* w, glfw::key::code button, glfw::key::action action, glfw::key::modifier mods) {
		std::cout << "mouse button: " << button << ", action = " << int(action) << ", mods = " <<  mods << std::endl;
	});

	w.set_cursor_pos_callback([](glfw::window* w, double x, double y) {
		std::cout << "cursor pos: x = " << x << ", y = " << y << std::endl;
	});

	w.set_cursor_enter_callback([](glfw::window* w, int entered) {
		std::cout << "cursor enter: " << bool(entered) << std::endl;
	});

	w.set_scroll_callback([](glfw::window* w, double offset_x, double offset_y) {
		std::cout << "scroll: x = " << offset_x << ", y = " << offset_y << std::endl;
	});

	w.set_key_callback([](glfw::window* w, glfw::key::code code, int scancode, glfw::key::action action, glfw::key::modifier modifiers) {
		std::cout << "key: code = " << code << ", scancode = " << scancode << ", action = " << int(action) << ", modifiers = " << modifiers << std::endl;
	});

	w.set_char_callback([](glfw::window* w, unsigned codepoint) {
		std::cout << "char: " << codepoint << std::endl;
	});

	while(w) {
		glfw::library.poll_events();
	}
}
#pragma once

#include "./handle.hpp"

extern "C" void glfwShowWindow(handle<glfw::window>::underlying_type window);

void handle_interface<glfw::window>::show() const {
	glfwShowWindow(underlying());
}
#pragma once

#include "./handle.hpp"
#include "../__internal/key.hpp"

extern "C" glfw::key_callback_t glfwSetKeyCallback(
	handle<glfw::window>::underlying_type window, glfw::key_callback_t callback
);

inline glfw::key_callback_t
handle_interface<glfw::window>::
set_key_callback(glfw::key_callback_t callback) const {
	return glfwSetKeyCallback(underlying(), callback);
}
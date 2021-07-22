#include "glfw/library.hpp"
#include "include.hpp"
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

namespace glfw {

int internal::init() noexcept {
	return glfwInit();
}

void internal::terminate() noexcept {
	glfwTerminate();
}

void internal::poll_events() noexcept {
	glfwPollEvents();
}

void internal::window_hint(int hint, int value) noexcept {
	glfwWindowHint(hint, value);
}

tl::expected<std::reference_wrapper<glfw::window>, glfw::error>
library_t::try_create_window(unsigned width, unsigned height, const char* title) const noexcept {
	if(GLFWwindow* handle = glfwCreateWindow(width, height, title, nullptr, nullptr)) {
		// UB
		return { *new(handle) glfw::window };
	}

	return tl::unexpected{ glfw::error{} };
}

}
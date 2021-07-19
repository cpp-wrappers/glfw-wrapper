#include "glfw/error.hpp"

#include "include.hpp"

namespace glfw::internal {
	int get_error(const char** desc) {
		return glfwGetError(desc);
	}
}
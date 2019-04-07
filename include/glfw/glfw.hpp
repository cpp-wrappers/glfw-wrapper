#include "window.hpp"
#include <string>
#include <vector>

namespace glfw {
	void poll_events() {
		glfwPollEvents();
	}
}
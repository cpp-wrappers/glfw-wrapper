#include "window.hpp"
#include <string>
#include <vector>

#include "monitor.hpp"

namespace glfw {
	

	inline void poll_events() {
		glfwPollEvents();
	}

	using error_callback = void(int code, const char* desc);

	inline void set_error_callback(error_callback cb) {
		glfwSetErrorCallback(cb);
	}

	using monitor_callback = void(monitor::event event);

	inline void set_monitor_callback(monitor_callback cb) {
		glfwSetMonitorCallback((GLFWmonitorfun)cb);
	}
}
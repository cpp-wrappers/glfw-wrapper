#pragma once

#include <string>
#include <functional>

namespace glfw {
	void poll_events();

	struct error {
		int code;
		std::string_view description;
	};

	using error_callback_t = std::function<void(error)>;

	void error_callback(error_callback_t cb);
}
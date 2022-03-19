#pragma once

#include "error.hpp"

extern "C" void abort();

namespace glfw {

	[[ noreturn ]]
	inline void default_unexpected_handler() {
		abort();
		__builtin_unreachable();
	}

	[[ noreturn ]]
	inline void default_unexpected_handler([[maybe_unused]] glfw::error result) {
		glfw::default_unexpected_handler();
	}

}
#pragma once

#include "error.hpp"

#ifndef GLFW_UNEXPECTED_HANDLER_HEADER

namespace glfw {

	[[ noreturn ]]
	inline void unexpected_handler();

	[[ noreturn ]]
	inline void unexpected_handler([[maybe_unused]] glfw::error result);

} // glfw

#else

#include_next GLFW_UNEXPECTED_HANDLER_HEADER

#endif
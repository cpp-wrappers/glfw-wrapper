#pragma once

#include "error.hpp"

#ifndef GLFW_UNEXPECTED_HANDLER_HEADER

namespace glfw {

	[[ noreturn ]]
	void unexpected_handler();

	[[ noreturn ]]
	void unexpected_handler(glfw::error);

} // glfw

#else

#include_next GLFW_UNEXPECTED_HANDLER_HEADER

#endif
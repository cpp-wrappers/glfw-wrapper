#pragma once

#include <stdexcept>
 
namespace glfw {

namespace internal {
	int get_error(const char** desc);
}

inline auto
get_error() noexcept {
	const char* str;
	int code = internal::get_error(&str);

	struct {
		int code;
		const char* description;
	} res{code, str};
	return res;
}

inline int get_error_code() noexcept {
	return internal::get_error(nullptr);
}

struct error : std::runtime_error {
	using std::runtime_error::runtime_error;
	error() : std::runtime_error{ get_error().description } {}
};

}
// from original headers

#if defined(_WIN32) && defined(_GLFW_BUILD_DLL)
	#define GLFW_API __declspec(dllexport)
#elif defined(_WIN32) && defined(GLFW_DLL)
	#define GLFW_API __declspec(dllimport)
#elif defined(__GNUC__) && defined(_GLFW_BUILD_DLL)
	#define GLFW_API __attribute__((visibility("default")))
#else
	#define GLFW_API
#endif
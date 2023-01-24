#pragma once

#include "../__internal/function.hpp"
#include "../__internal/error.hpp"
#include "../__window/create.hpp"

extern "C" GLFW_API int glfwInit();
extern "C" GLFW_API void glfwTerminate();

extern "C" GLFW_API void glfwPollEvents();
extern "C" GLFW_API void glfwWindowHint(int hint, int value);

#if __has_include(<vk/instance.hpp>)

	#include <vk/instance.hpp>

	extern "C" GLFW_API int glfwVulkanSupported(void);
	extern "C" GLFW_API const char**
		glfwGetRequiredInstanceExtensions(uint32* count);

	extern "C" GLFW_API void*
		glfwGetInstanceProcAddress(
			handle<vk::instance>::underlying_type instance,
			const char* proc_name
		);

#endif


namespace glfw {

	static constexpr int
		no_api = 0,
		client_api = 0x00022001;

	struct instance {

		instance() {
			if(!glfwInit()) {
				glfw::unexpected_handler();
			}
		}

		~instance() {
			glfwTerminate();
		}

		instance(      instance&&) = delete;
		instance(const instance& ) = delete;

		template<typename... Args>
		handle<glfw::window> create_window(Args&&... args) {
			return glfw::internal::create_window(forward<Args>(args)...);
		}

		inline void poll_events() const { glfwPollEvents(); }

		void window_hint(int hint, int value) {
			glfwWindowHint(hint, value);
		}

	#if __has_include(<vk/instance.hpp>)
		inline bool is_vulkan_supported() const {
			return glfwVulkanSupported();
		}

		inline void* get_global_proc_address(
			any_c_string auto proc_name
		) const {
			return glfwGetInstanceProcAddress(nullptr, proc_name.iterator());
		}

		inline void* get_instance_proc_address(
			handle<vk::instance> instance,
			any_c_string auto proc_name
		) const {
			return glfwGetInstanceProcAddress(
				instance.underlying(),
				proc_name.iterator()
			);
		}

		inline expected<span<vk::extension_name>, glfw::error>
		try_get_required_instance_extensions() const {
			uint32 count;
			const char** result = glfwGetRequiredInstanceExtensions(&count);
			if(result == nullptr) {
				return glfw::error{ glfw::get_error() };
			}
			return span<vk::extension_name> {
				(vk::extension_name*) result, count
			};
		}

		inline span<vk::extension_name>
		get_required_instance_extensions() const {
			auto result = this->try_get_required_instance_extensions();
			if(result.is_unexpected()) {
				glfw::unexpected_handler(result.get_unexpected());
			}
			return result.get_expected();
		}
	#endif


	};

}
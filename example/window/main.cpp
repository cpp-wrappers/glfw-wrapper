#include "glfw/window.hpp"
#include "glfw/glfw.hpp"
#include <iostream>

using namespace std;
using namespace glfw;

int main() {
	window w{800, 600, "test"};
	w.make_context_current();

	while(!w.should_close()){
		glfw::poll_events();
	}
}

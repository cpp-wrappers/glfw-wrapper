mkdir -p build
cd build

$CXX -c --std=c++17 -I../include $CXXARGS ../src/glfw.cpp

ar r glfw-wrapper.a glfw.o

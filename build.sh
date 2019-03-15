mkdir -p build
cd build

$CXX -c --std=c++17 -Iinclude $CXXARGS ../src/glfw.cpp

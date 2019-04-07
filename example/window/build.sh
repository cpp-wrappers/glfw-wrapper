cd ..
bash prepare_glfw.sh
cd window
mkdir build -p
cd build
clang++ -ggdb --std=c++17 -o window -I../../../include -I../../../glfw/include ../main.cpp ../../../glfw/build/src/libglfw.so

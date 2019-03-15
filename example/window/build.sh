../../bash build.sh
mkdir build
cd build
$CXX --std=c++17 $CXXARGS main.cpp -o window

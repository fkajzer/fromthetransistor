cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
project(metal_cpp_tutorial)

option(METAL_CPP_BUILD_EXAMPLES "Build examples" ON)

# metal cpp
add_subdirectory(metal-cmake)

if(METAL_CPP_BUILD_EXAMPLES)
	add_subdirectory(src)
endif(METAL_CPP_BUILD_EXAMPLES)

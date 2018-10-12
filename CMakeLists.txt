# This is a CMake file to build the mpags-cipher project 

# Set CMake requirements 
cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

# See all output by default to help us 
set(CMAKE_VERBOSE_MAKEFILE ON)

# Now get it to make an executable for us 
add_executable(mpags-cipher mpags-cipher.cpp)

# Turn off extensions to C++
set(CMAKE_CXX_EXTENSIONS OFF)

target_compile_features(mpags-cipher PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization)  

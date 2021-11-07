# CMakeList.txt : CMake project for cam, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)
project ("cam")

# Add source to this project's executable.
file(GLOB_RECURSE libsrc "src/*.c")
add_library(cam ${libsrc})
add_library(cam::cam ALIAS cam)
target_include_directories(cam PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

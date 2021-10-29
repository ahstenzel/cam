# CMakeList.txt : CMake project for cam, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("cam")

# Add source to this project's executable.
add_library (cam "src/cam.c" "include/cam.h" "include/common.h")

# TODO: Add tests and install targets if needed.

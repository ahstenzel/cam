# CMakeList.txt : CMake project for cam, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)
project ("cam")

## Specify library output directory
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin/static/${CMAKE_SYSTEM_PROCESSOR}")
if (BUILD_SHARED_LIBS)
  set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin/shared/${CMAKE_SYSTEM_PROCESSOR}")
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

# Add source to this project's executable.
file(GLOB_RECURSE libsrc "src/*.cpp")
#add_library(cam ${libsrc})
add_executable(cam ${libsrc})
target_include_directories(cam PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

# Add SIMD intrinsic switches
target_compile_options(cam PRIVATE $<IF:$<BOOL:${MSVC}>,/arch:AVX2,-mavx2>)

# Add platform specific libraries
if (NOT WIN32)
  target_link_libraries(cam m)
endif()
#pragma once
/*
 * transforms.hpp
 * Declaration for transformation matrix construction functions.
 */

#include "cam/linear/vec3.hpp"
#include "cam/linear/mat4.hpp"

namespace cam {
  mat4 matrix_translate(vec3 v);
  mat4 matrix_rotate(float a, vec3 v);
  mat4 matrix_scale(vec3 v);
  mat4 matrix_ortho(float left, float right, float near, float far, float top, float bottom);
  mat4 matrix_perspecive(float fov, float aspect, float near, float far);
  mat4 matrix_lookat(vec3 pos, vec3 target, vec3 up);
}
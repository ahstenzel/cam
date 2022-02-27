#pragma once
/*
 * transforms.hpp
 * Declaration for transformation matrix construction functions.
 */

#include "cam/linear/vec3.hpp"
#include "cam/linear/mat4.hpp"

namespace cam {
  mat4 matrix_translate(const vec3& v);
  mat4 matrix_rotate(float a, const vec3& v);
  mat4 matrix_scale(const vec3& v);
  mat4 matrix_ortho(float left, float right, float near, float far, float top, float bottom);
  mat4 matrix_perspecive(float fov, float aspect, float near, float far);
  mat4 matrix_lookat(const vec3& pos, const vec3& target, const vec3& up);
}
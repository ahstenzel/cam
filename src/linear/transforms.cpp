#pragma once
/*
 * transforms.cpp
 * Definition for transformation matrix construction functions.
 */

#include "cam/linear/transforms.hpp"

namespace cam {
  mat4 matrix_translate(vec3 v) {
    return mat4(
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      v.x(), v.y(), v.z(), 1.0f
    );
  }
  
  mat4 matrix_rotate(float a, vec3 v) {
    mat4 m;
    float c = (float)cos(a);
    float s = (float)sin(a);
    float x = v.x();
    float y = v.y();
    float z = v.z();

    m.at(0, 0) = c + (x * x * (1.0f - c));
    m.at(1, 0) = (y * x * (1.0f - c)) + (z * s);
    m.at(2, 0) = (z * x * (1.0f - c)) - (y * s);

    m.at(0, 1) = (x * y * (1.0f - c)) - (z * s);
    m.at(1, 1) = c + (y * y * (1.0f - c));
    m.at(2, 1) = (z * y * (1.0f - c)) + (x * s);

    m.at(0, 2) = (x * z * (1.0f - c)) + (y * s);
    m.at(1, 2) = (y * z * (1.0f - c)) - (x * s);
    m.at(2, 2) = c + (z * z * (1.0f - c));

    return m;
  }
  
  mat4 matrix_scale(vec3 v) {
    return mat4(
      v.x(), v.y(), v.z(), 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    );
  }
  
  mat4 matrix_ortho(float left, float right, float near, float far, float top, float bottom) {
    return mat4(
      2.0f/(right-left), 2.0f/(top-bottom), -2.0f/(far-near), 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      (right+left)/(right-left), (top+bottom)/(top-bottom), (far+near)/(far-near), 1.0f
    );
  }
  
  mat4 matrix_perspecive(float fov, float aspect, float near, float far) {
    float top = (float)tan(fov / 2.0f) * near;
    float bottom = -top;
    float right = top * aspect;
    float left = bottom * aspect;

    return mat4(
      (2.0f*near)/(right-left), (2.0f*near)/(top-bottom), 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      (right+left)/(right-left), (top+bottom)/(top-bottom), -(far+near)/(far-near), -1.0f,
      0.0f, 0.0f, (-2.0f*far*near)/(far-near), 0.0f
    );
  }

  mat4 matrix_lookat(vec3 pos, vec3 target, vec3 up) {
    mat4 t1;
    mat4 t2 = matrix_translate(pos * -1.0f);

    vec3 direc = (pos - target).normalize();
    vec3 right = (up - direc).normalize();
    vec3 camUp = vec3::cross_product(direc, right);

    t1.at(0, 0) = right.x();
    t1.at(0, 1) = camUp.x();
    t1.at(0, 2) = direc.x();

    t1.at(1, 0) = right.y();
    t1.at(1, 1) = camUp.y();
    t1.at(1, 2) = direc.y();

    t1.at(2, 0) = right.z();
    t1.at(2, 1) = camUp.z();
    t1.at(2, 2) = direc.z();

    return (t1 * t2);
  }
}
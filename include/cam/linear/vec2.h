/*
 * vec2.h
 * Declaration for 2D vector of floats.
 */

#ifndef CAM_LINEAR_VEC2_H
#define CAM_LINEAR_VEC2_H

#include "cam/linear/linear_common.h"

typedef struct {
  float data[2];
} vec2;

CAM_API vec2 make_vec2(float x, float y);
CAM_API vec2 vec2_zero();
CAM_API bool vec2_is_zero(vec2 v);

#endif

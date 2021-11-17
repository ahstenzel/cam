/*
 * vec2.h
 * Declaration for 2D vector of floats.
 */

#ifndef CAM_LINEAR_VEC2_H
#define CAM_LINEAR_VEC2_H

#include "cam/linear/linear_common.h"

/* Define vec2 struct */
typedef struct {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m256 data;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  float data[8];
#endif
} vec2;


CAM_API vec2 vec2_make(float x, float y);

CAM_API vec2 vec2_zero();

CAM_API bool vec2_is_zero(vec2 v);

#endif

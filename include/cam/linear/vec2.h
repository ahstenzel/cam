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
  __m128 data;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  float data[4];
#endif
} vec2;


/* vec2 functions */
CAM_API vec2 vec2_make(float x, float y);

CAM_API vec2 vec2_makez();

CAM_API float vec2_getx(vec2* v);

CAM_API float vec2_gety(vec2* v);

CAM_API void vec2_setx(vec2* v, float x);

CAM_API void vec2_sety(vec2* v, float y);

CAM_API bool vec2_equal(vec2* a, vec2* b);

CAM_API bool vec2_equalz(vec2* v);

CAM_API vec2 vec2_add(vec2* a, vec2* b);

CAM_API vec2 vec2_sub(vec2* a, vec2* b);

CAM_API vec2 vec2_mul(vec2* a, vec2* b);

CAM_API vec2 vec2_div(vec2* a, vec2* b);

CAM_API float vec2_mag(vec2* v);

CAM_API vec2 vec2_scale(vec2* a, float s);

CAM_API vec2 vec2_norm(vec2* v);

CAM_API float vec2_dist(vec2* a, vec2* b);

#endif

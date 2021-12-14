/*
 * vec4.h
 * Declaration for 4D vector of floats.
 */

#ifndef CAM_LINEAR_VEC4_H
#define CAM_LINEAR_VEC4_H

#include "cam/linear/linear_common.h"

/* Define vec4 struct */
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
} vec4;


/* vec4 functions */
CAM_API vec4 vec4_make(float x, float y, float z, float w);

CAM_API vec4 vec4_makez();

CAM_API float vec4_getx(vec4* v);

CAM_API float vec4_gety(vec4* v);

CAM_API float vec4_getw(vec4* v);

CAM_API float vec4_getz(vec4* v);

CAM_API void vec4_setx(vec4* v, float x);

CAM_API void vec4_sety(vec4* v, float y);

CAM_API void vec4_setz(vec4* v, float z);

CAM_API void vec4_setw(vec4* v, float z);

CAM_API bool vec4_equal(vec4* a, vec4* b);

CAM_API bool vec4_equalz(vec4* v);

CAM_API vec4 vec4_add(vec4* a, vec4* b);

CAM_API vec4 vec4_sub(vec4* a, vec4* b);

CAM_API vec4 vec4_mul(vec4* a, vec4* b);

CAM_API vec4 vec4_div(vec4* a, vec4* b);

CAM_API float vec4_mag(vec4* v);

CAM_API vec4 vec4_scale(vec4* a, float s);

CAM_API vec4 vec4_norm(vec4* v);

CAM_API float vec4_dist(vec4* a, vec4* b);

#endif

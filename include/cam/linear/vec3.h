/*
 * vec3.h
 * Declaration for 3D vector of floats.
 */

#ifndef CAM_LINEAR_VEC3_H
#define CAM_LINEAR_VEC3_H

#include "cam/linear/linear_common.h"

/* Define vec3 struct */
typedef struct {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 data;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  float32x4_t data;
#else
  // No SIMD intrinsics
  float data[4];
#endif
} vec3;


/* vec3 functions */
CAM_API vec3 vec3_make(float x, float y, float z);

CAM_API vec3 vec3_makez();

CAM_API float vec3_getx(vec3* v);

CAM_API float vec3_gety(vec3* v);

CAM_API float vec3_getz(vec3* v);

CAM_API void vec3_setx(vec3* v, float x);

CAM_API void vec3_sety(vec3* v, float y);

CAM_API void vec3_setz(vec3* v, float z);

CAM_API bool vec3_equal(vec3* a, vec3* b);

CAM_API bool vec3_equalz(vec3* v);

CAM_API vec3 vec3_add(vec3* a, vec3* b);

CAM_API vec3 vec3_sub(vec3* a, vec3* b);

CAM_API vec3 vec3_mul(vec3* a, vec3* b);

CAM_API vec3 vec3_div(vec3* a, vec3* b);

CAM_API float vec3_mag(vec3* v);

CAM_API vec3 vec3_scale(vec3* a, float s);

CAM_API vec3 vec3_norm(vec3* v);

CAM_API float vec3_dist(vec3* a, vec3* b);

#endif

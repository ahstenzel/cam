/*
 * vec2.c
 * Declaration for 2D vector of floats.
 */

#include "cam/linear/vec2.h"

vec2 vec2_make(float x, float y) {
  vec2 v;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  v.data = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, y, x);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  v.data[0] = x;
  v.data[1] = y;
  v.data[2] = 0.0f;
  v.data[3] = 0.0f;
  v.data[4] = 0.0f;
  v.data[5] = 0.0f;
  v.data[6] = 0.0f;
  v.data[7] = 0.0f;
#endif
  return v;
}

vec2 vec2_zero() {
  vec2 v;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  v.data = _mm256_setzero_ps();
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  v.data[0] = 0.0f;
  v.data[1] = 0.0f;
  v.data[2] = 0.0f;
  v.data[3] = 0.0f;
  v.data[4] = 0.0f;
  v.data[5] = 0.0f;
  v.data[6] = 0.0f;
  v.data[7] = 0.0f;
#endif
  return v;
}

bool vec2_is_zero(vec2 v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m256 vcmp = _mm256_cmp_ps(v.data, _mm256_setzero_ps(), _CMP_EQ_OQ);
  int mask = _mm256_movemask_ps(vcmp);
  return mask == 0xFF;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return (v.data[0] == 0.0f && v.data[1] == 0.0f);
#endif
}
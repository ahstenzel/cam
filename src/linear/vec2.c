/*
 * vec2.c
 * Declaration for 2D vector of floats.
 */

#include "cam/linear/vec2.h"

vec2 vec2_make(float x, float y) {
  vec2 v;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  v.data = _mm_set_ps(0.0f, 0.0f, y, x);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  v->data[0] = x;
  v->data[1] = y;
  v->data[2] = 0.0f;
  v->data[3] = 0.0f;
#endif
  return v;
}

vec2 vec2_makez() {
  vec2 v;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  v.data = _mm_setzero_ps();
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  v->data[0] = 0.0f;
  v->data[1] = 0.0f;
  v->data[2] = 0.0f;
  v->data[3] = 0.0f;
#endif
  return v;
}

float vec2_getx(vec2* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  return _mm_cvtss_f32(v->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return v->data[0];
#endif
}

float vec2_gety(vec2* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_shuffle_ps(v->data, v->data, 1);
  return _mm_cvtss_f32(tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return v->data[1];
#endif
}

void vec2_setx(vec2* v, float x) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps(0.0f, 0.0f, 0.0f, x);
  v->data = _mm_blend_ps(v->data, tmp, 0b0001);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  v->data[0] = x;
#endif
}

void vec2_sety(vec2* v, float y) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps(0.0f, 0.0f, y, 0.0f);
  v->data = _mm_blend_ps(v->data, tmp, 0b0010);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  v->data[1] = x;
#endif
}

bool vec2_equal(vec2* a, vec2* b) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 vcmp = _mm_cmp_ps(a->data, b->data, _CMP_EQ_OQ);
  int mask = _mm_movemask_ps(vcmp);
  return mask == 0xF;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return (a->data[0] == b->data[0] && 
          a->data[1] == b->data[1]);
#endif
}

bool vec2_equalz(vec2* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 vcmp = _mm_cmp_ps(v->data, _mm_setzero_ps(), _CMP_EQ_OQ);
  int mask = _mm_movemask_ps(vcmp);
  return mask == 0xF;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return (v->data[0] == 0.0f && 
          v->data[1] == 0.0f);
#endif
}

vec2 vec2_add(vec2* a, vec2* b) {
  vec2 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_add_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] + b->data[0];
  r.data[1] = a->data[1] + b->data[1];
#endif
  return r;
}

vec2 vec2_sub(vec2* a, vec2* b) {
  vec2 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_sub_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] - b->data[0];
  r.data[1] = a->data[1] - b->data[1];
#endif
  return r;
}

vec2 vec2_mul(vec2* a, vec2* b) {
  vec2 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_mul_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] * b->data[0];
  r.data[1] = a->data[1] * b->data[1];
#endif
  return r;
}

vec2 vec2_div(vec2* a, vec2* b) {
  vec2 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_div_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] / b->data[0];
  r.data[1] = a->data[1] / b->data[1];
#endif
  return r;
}

float vec2_mag(vec2* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_mul_ps(v->data, v->data);
  tmp = _mm_hadd_ps(tmp, tmp);
  return (float)sqrt(_mm_cvtss_f32(tmp));

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  float x = v->data[0];
  float y = v->data[1];
  return (float)sqrt(x * x + y * y);
#endif
}

vec2 vec2_scale(vec2* a, float s) {
  vec2 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps(0.0f, 0.0f, s, s);
  r.data = _mm_mul_ps(a->data, tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] * s;
  r.data[1] = a->data[1] * s;
#endif
  return r;
}

vec2 vec2_norm(vec2* v) {
  vec2 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_mul_ps(v->data, v->data);
  tmp = _mm_hadd_ps(tmp, tmp);
  tmp = _mm_sqrt_ps(tmp);
  r.data = _mm_div_ps(v->data, tmp);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  float x = v->data[0];
  float y = v->data[1];
  float mag = sqrt(x * x + y * y);
  r.data[0] = x / mag;
  r.data[1] = y / mag;
  
#endif
  return r;
}

float vec2_dist(vec2* a, vec2* b) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_sub_ps(a->data, b->data);
  tmp = _mm_mul_ps(tmp, tmp);
  tmp = _mm_hadd_ps(tmp, tmp);
  double mag = sqrt(_mm_cvtss_f32(tmp));
  return (float)fabs(mag);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  float x = a->data[0] - b->data[0];
  float y = a->data[1] - b->data[1];
  double mag = sqrt(x * x + y * y);
  return (float)fabs(mag);
#endif
}

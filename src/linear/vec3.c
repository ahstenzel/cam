/*
 * vec3.c
 * Declaration for 3D vector of floats.
 */

#include "cam/linear/vec3.h"

vec3 vec3_make(float x, float y, float z) {
  vec3 v;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  v.data = _mm_set_ps(0.0f, z, y, x);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  v->data[0] = x;
  v->data[1] = y;
  v->data[2] = z;
  v->data[3] = 0.0f;
#endif
  return v;
}

vec3 vec3_makez() {
  vec3 v;
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

float vec3_getx(vec3* v) {
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

float vec3_gety(vec3* v) {
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

float vec3_getz(vec3* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_shuffle_ps(v->data, v->data, 2);
  return _mm_cvtss_f32(tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return v->data[2];
#endif
}

void vec3_setx(vec3* v, float x) {
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

void vec3_sety(vec3* v, float y) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps(0.0f, 0.0f, y, 0.0f);
  v->data = _mm_blend_ps(v->data, tmp, 0b0010);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  v->data[1] = y;
#endif
}

void vec3_setz(vec3* v, float z) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps(0.0f, z, 0.0f, 0.0f);
  v->data = _mm_blend_ps(v->data, tmp, 0b0100);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  v->data[2] = z;
#endif
}

bool vec3_equal(vec3* a, vec3* b) {
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
          a->data[1] == b->data[1] &&
          a->data[2] == b->data[2]);
#endif
}

bool vec3_equalz(vec3* v) {
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
          v->data[1] == 0.0f &&
          v->data[2] == 0.0f);
#endif
}

vec3 vec3_add(vec3* a, vec3* b) {
  vec3 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_add_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] + b->data[0];
  r.data[1] = a->data[1] + b->data[1];
  r.data[2] = a->data[2] + b->data[2];
#endif
  return r;
}

vec3 vec3_sub(vec3* a, vec3* b) {
  vec3 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_sub_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] - b->data[0];
  r.data[1] = a->data[1] - b->data[1];
  r.data[2] = a->data[2] - b->data[2];
#endif
  return r;
}

vec3 vec3_mul(vec3* a, vec3* b) {
  vec3 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_mul_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] * b->data[0];
  r.data[1] = a->data[1] * b->data[1];
  r.data[2] = a->data[2] * b->data[2];
#endif
  return r;
}

vec3 vec3_div(vec3* a, vec3* b) {
  vec3 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_div_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] / b->data[0];
  r.data[1] = a->data[1] / b->data[1];
  r.data[2] = a->data[2] / b->data[2];
#endif
  return r;
}

float vec3_mag(vec3* v) {
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
  float z = v->data[2];
  return (float)sqrt(x * x + y * y + z * z);
#endif
}

vec3 vec3_scale(vec3* a, float s) {
  vec3 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps1(s);
  r.data = _mm_mul_ps(a->data, tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] * s;
  r.data[1] = a->data[1] * s;
  r.data[2] = a->data[2] * s;
#endif
  return r;
}

vec3 vec3_norm(vec3* v) {
  vec3 r;
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
  float z = v->data[2];
  float mag = sqrt(x * x + y * y + z * z);
  r.data[0] = x / mag;
  r.data[1] = y / mag;
  r.data[2] = z / mag;
  
#endif
  return r;
}

float vec3_dist(vec3* a, vec3* b) {
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
  float z = a->data[2] - b->data[2];
  double mag = sqrt(x * x + y * y + z * z);
  return (float)fabs(mag);
#endif
}

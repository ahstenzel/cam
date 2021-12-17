/*
 * vec4.c
 * Declaration for 3D vector of floats.
 */

#include "cam/linear/vec4.h"

vec4 vec4_make(float x, float y, float z, float w) {
  vec4 v;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  v.data = _mm_set_ps(w, z, y, x);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  float arr[4] = {x, y, z, w};
  v.data = vld1q_f32(arr);
#else
  // No SIMD intrinsics
  v->data[0] = x;
  v->data[1] = y;
  v->data[2] = z;
  v->data[3] = w;
#endif
  return v;
}

vec4 vec4_makez() {
  vec4 v;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  v.data = _mm_setzero_ps();
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  v.data = vmovq_n_f32(0.0f);
#else
  // No SIMD intrinsics
  v->data[0] = 0.0f;
  v->data[1] = 0.0f;
  v->data[2] = 0.0f;
  v->data[3] = 0.0f;
#endif
  return v;
}

float vec4_getx(vec4* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  return _mm_cvtss_f32(v->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  return vgetq_lane_f32(v->data, 0);
#else
  // No SIMD intrinsics
  return v->data[0];
#endif
}

float vec4_gety(vec4* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_shuffle_ps(v->data, v->data, 1);
  return _mm_cvtss_f32(tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  return vgetq_lane_f32(v->data, 1);
#else
  // No SIMD intrinsics
  return v->data[1];
#endif
}

float vec4_getz(vec4* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_shuffle_ps(v->data, v->data, 2);
  return _mm_cvtss_f32(tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  return vgetq_lane_f32(v->data, 2);
#else
  // No SIMD intrinsics
  return v->data[2];
#endif
}

float vec4_getw(vec4* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_shuffle_ps(v->data, v->data, 3);
  return _mm_cvtss_f32(tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  return vgetq_lane_f32(v->data, 3);
#else
  // No SIMD intrinsics
  return v->data[2];
#endif
}

void vec4_setx(vec4* v, float x) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps(0.0f, 0.0f, 0.0f, x);
  v->data = _mm_blend_ps(v->data, tmp, 0b0001);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  v->data = vsetq_lane_f32(x, v->data, 0);
#else
  // No SIMD intrinsics
  v->data[0] = x;
#endif
}

void vec4_sety(vec4* v, float y) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps(0.0f, 0.0f, y, 0.0f);
  v->data = _mm_blend_ps(v->data, tmp, 0b0010);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  v->data = vsetq_lane_f32(y, v->data, 1);
#else
  // No SIMD intrinsics
  v->data[1] = y;
#endif
}

void vec4_setz(vec4* v, float z) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps(0.0f, z, 0.0f, 0.0f);
  v->data = _mm_blend_ps(v->data, tmp, 0b0100);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  v->data = vsetq_lane_f32(z, v->data, 2);
#else
  // No SIMD intrinsics
  v->data[2] = z;
#endif
}

void vec4_setw(vec4* v, float w) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps(w, 0.0f, 0.0f, 0.0f);
  v->data = _mm_blend_ps(v->data, tmp, 0b0100);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  v->data = vsetq_lane_f32(w, v->data, 3);
#else
  // No SIMD intrinsics
  v->data[3] = w;
#endif
}

bool vec4_equal(vec4* a, vec4* b) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 vcmp = _mm_cmp_ps(a->data, b->data, _CMP_EQ_OQ);
  int mask = _mm_movemask_ps(vcmp);
  return mask == 0xF;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  uint32x4_t result = vceqq_f32(a->data, b->data);
  return (vminvq_u32(result) != 0);
#else
  // No SIMD intrinsics
  return (a->data[0] == b->data[0] && 
          a->data[1] == b->data[1] &&
          a->data[2] == b->data[2] &&
          a->data[3] == b->data[3]);
#endif
}

bool vec4_equalz(vec4* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 vcmp = _mm_cmp_ps(v->data, _mm_setzero_ps(), _CMP_EQ_OQ);
  int mask = _mm_movemask_ps(vcmp);
  return mask == 0xF;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  uint32x4_t result = vceqzq_f32(v->data);
  return (vminvq_u32(result) != 0);
#else
  // No SIMD intrinsics
  return (v->data[0] == 0.0f && 
          v->data[1] == 0.0f &&
          v->data[2] == 0.0f &&
          v->data[3] == 0.0f);
#endif
}

vec4 vec4_add(vec4* a, vec4* b) {
  vec4 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_add_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  r.data = vaddq_f32(a->data, b->data);
#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] + b->data[0];
  r.data[1] = a->data[1] + b->data[1];
  r.data[2] = a->data[2] + b->data[2];
  r.data[3] = a->data[3] + b->data[3];
#endif
  return r;
}

vec4 vec4_sub(vec4* a, vec4* b) {
  vec4 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_sub_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  r.data = vsubq_f32(a->data, b->data);
#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] - b->data[0];
  r.data[1] = a->data[1] - b->data[1];
  r.data[2] = a->data[2] - b->data[2];
  r.data[3] = a->data[3] - b->data[3];
#endif
  return r;
}

vec4 vec4_mul(vec4* a, vec4* b) {
  vec4 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_mul_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  r.data = vmulq_f32(a->data, b->data);
#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] * b->data[0];
  r.data[1] = a->data[1] * b->data[1];
  r.data[2] = a->data[2] * b->data[2];
  r.data[3] = a->data[3] * b->data[3];
#endif
  return r;
}

vec4 vec4_div(vec4* a, vec4* b) {
  vec4 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  r.data = _mm_div_ps(a->data, b->data);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  r.data = vdivq_f32(a->data, b->data);
#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] / b->data[0];
  r.data[1] = a->data[1] / b->data[1];
  r.data[2] = a->data[2] / b->data[2];
  r.data[3] = a->data[3] / b->data[3];
#endif
  return r;
}

float vec4_mag(vec4* v) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_mul_ps(v->data, v->data);
  tmp = _mm_hadd_ps(tmp, tmp);
  return (float)sqrt(_mm_cvtss_f32(tmp));

#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  float32x4_t tmp = vmulq_f32(v->data, v->data);
  tmp = vpaddq_f32(tmp, tmp);
  return (float)sqrt(vgetq_lane_f32(tmp, 0));
#else
  // No SIMD intrinsics
  float x = v->data[0];
  float y = v->data[1];
  float z = v->data[2];
  float w = v->data[3];
  return (float)sqrt(x * x + y * y + z * z + w * w);
#endif
}

vec4 vec4_scale(vec4* a, float s) {
  vec4 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps1(s);
  r.data = _mm_mul_ps(a->data, tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  r.data = vmulq_n_f32(a->data, s);
#else
  // No SIMD intrinsics
  r.data[0] = a->data[0] * s;
  r.data[1] = a->data[1] * s;
  r.data[2] = a->data[2] * s;
  r.data[3] = a->data[3] * s;
#endif
  return r;
}

vec4 vec4_norm(vec4* v) {
  vec4 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_mul_ps(v->data, v->data);
  tmp = _mm_hadd_ps(tmp, tmp);
  tmp = _mm_sqrt_ps(tmp);
  r.data = _mm_div_ps(v->data, tmp);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  float32x4_t tmp = vmulq_f32(v->data, v->data);
  tmp = vpaddq_f32(tmp, tmp);
  float s = (float)sqrt(vgetq_lane_f32(tmp, 0));
  r.data = vmulq_n_f32(v->data, 1.0f/s);
#else
  // No SIMD intrinsics
  float x = v->data[0];
  float y = v->data[1];
  float z = v->data[2];
  float w = v->data[3];
  float mag = sqrt(x * x + y * y + z * z + w * w);
  r.data[0] = x / mag;
  r.data[1] = y / mag;
  r.data[2] = z / mag;
  r.data[3] = 2 / mag;
  
#endif
  return r;
}

float vec4_dist(vec4* a, vec4* b) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_sub_ps(a->data, b->data);
  tmp = _mm_mul_ps(tmp, tmp);
  tmp = _mm_hadd_ps(tmp, tmp);
  double mag = sqrt(_mm_cvtss_f32(tmp));
  return (float)fabs(mag);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON
  float32x4_t tmp = vsubq_f32(a->data, b->data);
  tmp = vmulq_f32(tmp, tmp);
  tmp = vpaddq_f32(tmp, tmp);
  double mag = sqrt(vgetq_lane_f32(tmp, 0));
  return (float)fabs(mag);
#else
  // No SIMD intrinsics
  float x = a->data[0] - b->data[0];
  float y = a->data[1] - b->data[1];
  float z = a->data[2] - b->data[2];
  float w = a->data[3] - b->data[3];
  double mag = sqrt(x * x + y * y + z * z + w * w);
  return (float)fabs(mag);
#endif
}

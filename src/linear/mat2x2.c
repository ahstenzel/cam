/*
 * mat2x2.c
 * Declaration for 2x2 matrix of floats in column-major order.
 */

#include "cam/linear/mat2x2.h"

 /* mat2x2 functions */
#if defined(CAM_SIMD_AVX)
CAM_API __m128 __mat2x2_get_row(mat2x2* m, unsigned int row) {
  if (row == 0) { 
    __m128 t = _mm_shuffle_ps(m->data[0], m->data[0], 0);
    return _mm_insert_ps(t, m->data[1], 0b00010000);
  }
  else { 
    __m128 t = _mm_shuffle_ps(m->data[0], m->data[0], 1);
    return _mm_insert_ps(t, m->data[1], 0b01010000);
  }
}
#endif

mat2x2 mat2x2_make(float x1, float y1, float x2, float y2) {
  mat2x2 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  n.data[0] = _mm_set_ps(0.0f, 0.0f, y1, x1);
  n.data[1] = _mm_set_ps(0.0f, 0.0f, y2, x2);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = x1;
  n.data[1] = y1;
  n.data[2] = x2;
  n.data[3] = y2;
#endif
  return n;
}

mat2x2 mat2x2_makeid() {
  mat2x2 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  n.data[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
  n.data[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = 1.0f;
  n.data[1] = 0.0f;
  n.data[2] = 0.0f;
  n.data[3] = 1.0f;
#endif
  return n;
}

bool mat2x2_equal(mat2x2* a, mat2x2* b) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 vcmp = _mm_cmpeq_ps(a->data[0], b->data[0]);
  int mask = _mm_movemask_ps(vcmp);
  vcmp = _mm_cmpeq_ps(a->data[1], b->data[1]);
  mask &= _mm_movemask_ps(vcmp);
  return mask == 0xF;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return (a->data[0] == b->data[0] &&
          a->data[1] == b->data[1] &&
          a->data[2] == b->data[2] &&
          a->data[3] == b->data[3]);
#endif
}

bool mat2x2_equalid(mat2x2* m) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 vcmp = _mm_cmpeq_ps(m->data[0], _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f));
  int mask = _mm_movemask_ps(vcmp);
  vcmp = _mm_cmpeq_ps(m->data[1], _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f));
  mask &= _mm_movemask_ps(vcmp);
  return mask == 0xF;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return (m->data[0] == 1.0f &&
          m->data[1] == 0.0f &&
          m->data[2] == 0.0f &&
          m->data[3] == 1.0f);
#endif
}

float mat2x2_get(unsigned int col, unsigned int row, mat2x2* m) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 n = m->data[col];
  __m128 tmp;
  if (row == 0) { tmp = _mm_shuffle_ps(n, n, 0); }
  else { tmp = _mm_shuffle_ps(n, n, 1); }
  return _mm_cvtss_f32(tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return m->data[(col * 2) + row];
#endif
}

mat2x2 mat2x2_add(mat2x2* a, mat2x2* b) {
  mat2x2 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  n.data[0] = _mm_add_ps(a->data[0], b->data[0]);
  n.data[1] = _mm_add_ps(a->data[1], b->data[1]);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = a->data[0] + b->data[0];
  n.data[1] = a->data[1] + b->data[1];
  n.data[2] = a->data[2] + b->data[2];
  n.data[3] = a->data[3] + b->data[3];
#endif
  return n;
}

mat2x2 mat2x2_sub(mat2x2* a, mat2x2* b) {
  mat2x2 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  n.data[0] = _mm_sub_ps(a->data[0], b->data[0]);
  n.data[1] = _mm_sub_ps(a->data[1], b->data[1]);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = a->data[0] - b->data[0];
  n.data[1] = a->data[1] - b->data[1];
  n.data[2] = a->data[2] - b->data[2];
  n.data[3] = a->data[3] - b->data[3];
#endif
  return n;
}

mat2x2 mat2x2_scale(mat2x2* m, float s) {
  mat2x2 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps1(s);
  n.data[0] = _mm_mul_ps(m->data[0], tmp);
  n.data[1] = _mm_mul_ps(m->data[1], tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = m->data[0] * s;
  n.data[1] = m->data[1] * s;
  n.data[2] = m->data[2] * s;
  n.data[3] = m->data[3] * s;
#endif
  return n;
}

mat2x2 mat2x2_mul(mat2x2* a, mat2x2* b) {
  mat2x2 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  float buff[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  
  __m128 v1 = __mat2x2_get_row(a, 0);
  __m128 v2 = b->data[0];
  buff[0] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v2 = b->data[1];
  buff[2] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v1 = __mat2x2_get_row(a, 1);
  v2 = b->data[0];
  buff[1] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v2 = b->data[1];
  buff[3] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  n.data[0] = _mm_set_ps(0.0f, 0.0f, buff[1], buff[0]);
  n.data[1] = _mm_set_ps(0.0f, 0.0f, buff[3], buff[2]);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = (a->data[0] * b->data[0]) + (a->data[2] * b->data[1]);
  n.data[1] = (a->data[1] * b->data[0]) + (a->data[3] * b->data[1]);
  n.data[2] = (a->data[0] * b->data[2]) + (a->data[2] * b->data[3]);
  n.data[3] = (a->data[1] * b->data[2]) + (a->data[3] * b->data[3]);
#endif
  return n;
}

vec2 mat2x2_vec2_mul(mat2x2* m, vec2* v) {
  vec2 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  float buff[2] = { 0.0f, 0.0f };

  __m128 a = __mat2x2_get_row(m, 0);
  buff[0] = _mm_cvtss_f32(_mm_dp_ps(a, v->data, 0xFF));

  a = __mat2x2_get_row(m, 1);
  buff[1] = _mm_cvtss_f32(_mm_dp_ps(a, v->data, 0xFF));

  r.data = _mm_set_ps(0.0f, 0.0f, buff[1], buff[0]);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  r.data[0] = (m->data[0] * v->data[0]) + (m->data[2] * v->data[1]);
  r.data[1] = (m->data[1] * v->data[0]) + (m->data[3] * v->data[1]);
#endif
  return r;
}

mat2x2 mat2x2_transpose(mat2x2* m) {
  mat2x2 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 t0 = _mm_unpacklo_ps(m->data[0], m->data[1]);
  n.data[0] = _mm_movelh_ps(t0, _mm_setzero_ps());
  n.data[1] = _mm_movehl_ps(_mm_setzero_ps(), t0);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = m->data[0];
  n.data[1] = m->data[2];
  n.data[2] = m->data[1];
  n.data[3] = m->data[3];
#endif
  return n;
}

float mat2x2_det(mat2x2* m) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_unpacklo_ps(m->data[0], m->data[1]);
  __m128 t0 = _mm_shuffle_ps(tmp, _mm_setzero_ps(), 0b00001000);
  __m128 t1 = _mm_shuffle_ps(tmp, _mm_setzero_ps(), 0b00000111);
  t1 = _mm_mul_ps(t1, _mm_set_ps(0.0f, 0.0f, -1.0f, 1.0f));
  tmp = _mm_dp_ps(t0, t1, 0xFF);
  return _mm_cvtss_f32(tmp);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return ((m->data[0] * m->data[3]) - (m->data[1] * m->data[2]));

#endif
}
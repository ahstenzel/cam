/*
 * mat3x3.c
 * Declaration for 3x3 matrix of floats in column-major order.
 */

#include "cam/linear/mat3x3.h"

 /* mat3x3 functions */
#if defined(CAM_SIMD_AVX)
CAM_API __m128 __mat3x3_get_row(mat3x3* m, unsigned int row) {
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

mat3x3 mat3x3_make(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
  mat3x3 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  n.data[0] = _mm_set_ps(0.0f, z1, y1, x1);
  n.data[1] = _mm_set_ps(0.0f, z2, y2, x2);
  n.data[2] = _mm_set_ps(0.0f, z3, y3, x3);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = x1;
  n.data[1] = y1;
  n.data[2] = z1;
  n.data[3] = x2;
  n.data[4] = y2;
  n.data[5] = z2;
  n.data[6] = x3;
  n.data[7] = y3;
  n.data[8] = z3;
#endif
  return n;
}

mat3x3 mat3x3_makeid() {
  mat3x3 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  n.data[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
  n.data[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
  n.data[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = 1.0f;
  n.data[1] = 0.0f;
  n.data[2] = 0.0f;
  n.data[3] = 0.0f;
  n.data[4] = 1.0f;
  n.data[5] = 0.0f;
  n.data[6] = 0.0f;
  n.data[7] = 0.0f;
  n.data[8] = 1.0f;
#endif
  return n;
}

bool mat3x3_equal(mat3x3* a, mat3x3* b) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 vcmp = _mm_cmpeq_ps(a->data[0], b->data[0]);
  int mask = _mm_movemask_ps(vcmp);
  vcmp = _mm_cmpeq_ps(a->data[1], b->data[1]);
  mask &= _mm_movemask_ps(vcmp);
  vcmp = _mm_cmpeq_ps(a->data[2], b->data[2]);
  mask &= _mm_movemask_ps(vcmp);
  return mask == 0xF;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return (a->data[0] == b->data[0] &&
          a->data[1] == b->data[1] &&
          a->data[2] == b->data[2] &&
          a->data[3] == b->data[3] &&
          a->data[4] == b->data[4] &&
          a->data[5] == b->data[5] &&
          a->data[6] == b->data[6] &&
          a->data[7] == b->data[7] &&
          a->data[8] == b->data[8]);
#endif
}

bool mat3x3_equalid(mat3x3* m) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 vcmp = _mm_cmpeq_ps(m->data[0], _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f));
  int mask = _mm_movemask_ps(vcmp);
  vcmp = _mm_cmpeq_ps(m->data[1], _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f));
  mask &= _mm_movemask_ps(vcmp);
  vcmp = _mm_cmpeq_ps(m->data[2], _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f));
  mask &= _mm_movemask_ps(vcmp);
  return mask == 0xF;
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return (m->data[0] == 1.0f &&
          m->data[1] == 0.0f &&
          m->data[2] == 0.0f &&
          m->data[3] == 0.0f &&
          m->data[4] == 1.0f &&
          m->data[5] == 0.0f &&
          m->data[6] == 0.0f &&
          m->data[7] == 0.0f &&
          m->data[8] == 1.0f);
#endif
}

float mat3x3_get(unsigned int col, unsigned int row, mat3x3* m) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 n = m->data[col];
  __m128 tmp;
       if (row == 0) { tmp = _mm_shuffle_ps(n, n, 0); } // Compiler doesn't like a variable here?
  else if (row == 1) { tmp = _mm_shuffle_ps(n, n, 1); }
  else if (row == 2) { tmp = _mm_shuffle_ps(n, n, 2); }
  return _mm_cvtss_f32(tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  return m->data[(col * 3) + row];
#endif
}

mat3x3 mat3x3_add(mat3x3* a, mat3x3* b) {
  mat3x3 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  n.data[0] = _mm_add_ps(a->data[0], b->data[0]);
  n.data[1] = _mm_add_ps(a->data[1], b->data[1]);
  n.data[2] = _mm_add_ps(a->data[2], b->data[2]);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = a->data[0] + b->data[0];
  n.data[1] = a->data[1] + b->data[1];
  n.data[2] = a->data[2] + b->data[2];
  n.data[3] = a->data[3] + b->data[3];
  n.data[4] = a->data[4] + b->data[4];
  n.data[5] = a->data[5] + b->data[5];
  n.data[6] = a->data[6] + b->data[6];
  n.data[7] = a->data[7] + b->data[7];
  n.data[8] = a->data[8] + b->data[8];
#endif
  return n;
}

mat3x3 mat3x3_sub(mat3x3* a, mat3x3* b) {
  mat3x3 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  n.data[0] = _mm_sub_ps(a->data[0], b->data[0]);
  n.data[1] = _mm_sub_ps(a->data[1], b->data[1]);
  n.data[2] = _mm_sub_ps(a->data[2], b->data[2]);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = a->data[0] - b->data[0];
  n.data[1] = a->data[1] - b->data[1];
  n.data[2] = a->data[2] - b->data[2];
  n.data[3] = a->data[3] - b->data[3];
  n.data[4] = a->data[4] - b->data[4];
  n.data[5] = a->data[5] - b->data[5];
  n.data[6] = a->data[6] - b->data[6];
  n.data[7] = a->data[7] - b->data[7];
  n.data[8] = a->data[8] - b->data[8];
#endif
  return n;
}

mat3x3 mat3x3_scale(mat3x3* m, float s) {
  mat3x3 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 tmp = _mm_set_ps1(s);
  n.data[0] = _mm_mul_ps(m->data[0], tmp);
  n.data[1] = _mm_mul_ps(m->data[1], tmp);
  n.data[2] = _mm_mul_ps(m->data[2], tmp);
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = m->data[0] * s;
  n.data[1] = m->data[1] * s;
  n.data[2] = m->data[2] * s;
  n.data[3] = m->data[3] * s;
  n.data[4] = m->data[4] * s;
  n.data[5] = m->data[5] * s;
  n.data[6] = m->data[6] * s;
  n.data[7] = m->data[7] * s;
  n.data[8] = m->data[8] * s;
#endif
  return n;
}

mat3x3 mat3x3_mul(mat3x3* a, mat3x3* b) {
  mat3x3 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  float buff[9] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  
  __m128 v1 = __mat3x3_get_row(a, 0);
  __m128 v2 = b->data[0];
  buff[0] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v2 = b->data[1];
  buff[3] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v2 = b->data[2];
  buff[6] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v1 = __mat3x3_get_row(a, 1);
  v2 = b->data[0];
  buff[1] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v2 = b->data[1];
  buff[4] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v2 = b->data[2];
  buff[7] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v1 = __mat3x3_get_row(a, 2);
  v2 = b->data[0];
  buff[2] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v2 = b->data[1];
  buff[5] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  v2 = b->data[2];
  buff[8] = _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0xFF));

  n.data[0] = _mm_set_ps(0.0f, buff[2], buff[1], buff[0]);
  n.data[1] = _mm_set_ps(0.0f, buff[5], buff[4], buff[3]);
  n.data[2] = _mm_set_ps(0.0f, buff[8], buff[7], buff[6]);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  //n.data[0] = (a->data[0] * b->data[0]) + (a->data[2] * b->data[1]);
  //n.data[1] = (a->data[1] * b->data[0]) + (a->data[3] * b->data[1]);
  //n.data[2] = (a->data[0] * b->data[2]) + (a->data[2] * b->data[3]);
  //n.data[3] = (a->data[1] * b->data[2]) + (a->data[3] * b->data[3]);
#endif
  return n;
}

vec3 mat3x3_vec3_mul(mat3x3* m, vec3* v) {
  vec3 r;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  float buff[3] = { 0.0f, 0.0f, 0.0f };

  __m128 a = __mat3x3_get_row(m, 0);
  buff[0] = _mm_cvtss_f32(_mm_dp_ps(a, v->data, 0xFF));

  a = __mat3x3_get_row(m, 1);
  buff[1] = _mm_cvtss_f32(_mm_dp_ps(a, v->data, 0xFF));

  a = __mat3x3_get_row(m, 2);
  buff[2] = _mm_cvtss_f32(_mm_dp_ps(a, v->data, 0xFF));

  r.data = _mm_set_ps(0.0f, buff[2], buff[1], buff[0]);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  //r.data[0] = (m->data[0] * v->data[0]) + (m->data[2] * v->data[1]);
  //r.data[1] = (m->data[1] * v->data[0]) + (m->data[3] * v->data[1]);
#endif
  return r;
}

mat3x3 mat3x3_transpose(mat3x3* m) {
  mat3x3 n;
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  //__m128 t0 = _mm_unpacklo_ps(m->data[0], m->data[1]);
  //n.data[0] = _mm_movelh_ps(t0, _mm_setzero_ps());
  //n.data[1] = _mm_movehl_ps(_mm_setzero_ps(), t0);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  n.data[0] = m->data[0];
  n.data[1] = m->data[3];
  n.data[2] = m->data[6];
  n.data[3] = m->data[1];
  n.data[4] = m->data[4];
  n.data[5] = m->data[7];
  n.data[6] = m->data[2];
  n.data[7] = m->data[5];
  n.data[8] = m->data[8];
#endif
  return n;
}

float mat3x3_det(mat3x3* m) {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  //__m128 tmp = _mm_unpacklo_ps(m->data[0], m->data[1]);
  //__m128 t0 = _mm_shuffle_ps(tmp, _mm_setzero_ps(), 0b00001000);
  //__m128 t1 = _mm_shuffle_ps(tmp, _mm_setzero_ps(), 0b00000111);
  //t1 = _mm_mul_ps(t1, _mm_set_ps(0.0f, 0.0f, -1.0f, 1.0f));
  //tmp = _mm_dp_ps(t0, t1, 0xFF);
  //return _mm_cvtss_f32(tmp);

#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  //return ((m->data[0] * m->data[3]) - (m->data[1] * m->data[2]));

#endif
}
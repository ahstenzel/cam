/*
 * mat3x3.h
 * Declaration for 3x3 matrix of floats in column-major order.
 */

#ifndef CAM_LINEAR_MAT3X3_H
#define CAM_LINEAR_MAT3X3_H

#include "cam/linear/linear_common.h"
#include "cam/linear/vec3.h"

 /* Define mat3x3 struct */
typedef struct {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 data[3];
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  float data[4];
#endif
} mat3x3;


/* mat3x3 functions */
#if defined(CAM_SIMD_AVX)
CAM_API __m128 __mat3x3_get_row(mat3x3* m, unsigned int row);
#endif

CAM_API mat3x3 mat3x3_make(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

CAM_API mat3x3 mat3x3_makeid();

CAM_API bool mat3x3_equal(mat3x3* a, mat3x3* b);

CAM_API bool mat3x3_equalid(mat3x3* m);

CAM_API float mat3x3_get(unsigned int col, unsigned int row, mat3x3* m);

CAM_API mat3x3 mat3x3_add(mat3x3* a, mat3x3* b);

CAM_API mat3x3 mat3x3_sub(mat3x3* a, mat3x3* b);

CAM_API mat3x3 mat3x3_scale(mat3x3* m, float s);

CAM_API mat3x3 mat3x3_mul(mat3x3* a, mat3x3* b);

CAM_API vec2 mat3x3_vec3_mul(mat3x3* m, vec3* v);

CAM_API mat3x3 mat3x3_transpose(mat3x3* m);

CAM_API float mat3x3_det(mat3x3* m);

#endif

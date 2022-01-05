/*
 * mat2x2.h
 * Declaration for 2x2 matrix of floats in column-major order.
 */

#ifndef CAM_LINEAR_MAT2X2_H
#define CAM_LINEAR_MAT2X2_H

#include "cam/linear/linear_common.h"
#include "cam/linear/vec2.h"

 /* Define mat2x2 struct */
typedef struct {
#if defined(CAM_SIMD_AVX)
  // Intel AVX
  __m128 data[2];
#elif defined(CAM_SIMD_NEON)
  // AMD NEON

#else
  // No SIMD intrinsics
  float data[4];
#endif
} mat2x2;


/* mat2x2 functions */
#if defined(CAM_SIMD_AVX)
CAM_API __m128 __mat2x2_get_row(mat2x2* m, unsigned int row);
#endif

CAM_API mat2x2 mat2x2_make(float x1, float y1, float x2, float y2);

CAM_API mat2x2 mat2x2_makeid();

CAM_API bool mat2x2_equal(mat2x2* a, mat2x2* b);

CAM_API bool mat2x2_equalid(mat2x2* m);

CAM_API float mat2x2_get(unsigned int col, unsigned int row, mat2x2* m);

CAM_API mat2x2 mat2x2_add(mat2x2* a, mat2x2* b);

CAM_API mat2x2 mat2x2_sub(mat2x2* a, mat2x2* b);

CAM_API mat2x2 mat2x2_scale(mat2x2* m, float s);

CAM_API mat2x2 mat2x2_mul(mat2x2* a, mat2x2* b);

CAM_API vec2 mat2x2_vec2_mul(mat2x2* m, vec2* v);

CAM_API mat2x2 mat2x2_transpose(mat2x2* m);

CAM_API float mat2x2_det(mat2x2* m);

#endif

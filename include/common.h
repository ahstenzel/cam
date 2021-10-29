#ifndef CAM_COMMON_H
#define CAM_COMMON_H

#include <stdio.h>
#include <math.h>         // Standard trig functions
#include <immintrin.h>    // Intel SIMD instructions

#ifndef CAM_EXCLUDE_DEFINES
#define C_E        2.71828182845904523536   // e
#define C_LOG2E    1.44269504088896340736   // log2(e)
#define C_LOG10E   0.434294481903251827651  // log10(e)
#define C_LN2      0.693147180559945309417  // ln(2)
#define C_LN10     2.30258509299404568402   // ln(10)
#define C_PI       3.14159265358979323846   // pi
#define C_PI_2     1.57079632679489661923   // pi/2
#define C_PI_4     0.785398163397448309616  // pi/4
#define C_SQRT2    1.41421356237309504880   // sqrt(2)
#define C_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)
#endif

#endif

/*
 * common.h
 * Common definitions and inclusions across the project.
 */

#ifndef CAM_COMMON_H
#define CAM_COMMON_H

/* Standard library includes */
#include <stdio.h>    // Console IO
#include <stdbool.h>  // Boolean values
#include <limits.h>   // Numeric limits
#include <stdint.h>   // Regular sized integers
#if defined(_MSC_VER)
#include <intrin.h>   // CPU feature detection
#endif


/* Detect architecture */
#if defined(__arm__) || defined(__thumb__) ||\
    defined(_M_ARM)  || defined(_M_ARMT)
# define CAM_ARCH_ARM
#elif defined(__aarch64__) || defined (_M_ARM64)
# define CAM_ARCH_ARM64
#elif defined(i386) || defined(__i386) || defined(__i386__) ||\
      defined(i486) || defined(__i486) || defined(__i486__) ||\
      defined(i586) || defined(__i586) || defined(__i586__) ||\
      defined(i686) || defined(__i686) || defined(__i686__) ||\
      defined(_M_IX86) || defined(_M_X86) || defined(_X86_)
# define CAM_ARCH_X86
#elif defined(__x86_64) || defined(__x86_64__) ||\
      defined(__amd64) || defined(__amd64__) ||\
      defined(_M_X64) || defined(_M_AMD64)
# define CAM_ARCH_X64
#else
# define CAM_ARCH_UNKNOWN
#endif


/* SIMD Definitions */
#if defined(CAM_ARCH_X86) || defined(CAM_ARCH_X64) && !defined(CAM_LEGACY)
# define CAM_SIMD_AVX
#include <immintrin.h>

#elif defined(CAM_ARCH_ARM) || defined(CAM_ARCH_ARM64) && !defined(CAM_LEGACY)
# define CAM_SIMD_NEON

#else
# define CAM_SIMD_NONE

#endif


/* Useful definitions */
#ifndef CAM_EXCLUDE_DEFINES
// Ensure std math lib doesnt include its definitions as well
#ifdef _USE_MATH_DEFINES
#undef _USE_MATH_DEFINES
#endif
#include <math.h>         // Standard trig functions

// Math constants
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

// Useful functions
#define radtodeg(a) (a * (180.0 / C_PI))
#define degtorad(a) (a * (C_PI / 180.0))
#else
#define _USE_MATH_DEFINES
#include <math.h>
#endif


/* DLL export/import */
#ifdef CAM_SHARED_DEFINE
#ifdef CAM_EXPORTS
#define CAM_API __declspec(dllexport)
#else
#define CAM_API __declspec(dllimport)
#endif
#else
#define CAM_API
#endif


#endif

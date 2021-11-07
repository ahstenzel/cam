/*
 * vec2.c
 * Declaration for 2D vector of floats.
 */

#include "cam/linear/vec2.h"

vec2 make_vec2(float x, float y) {
  vec2 v;
  v.X = x;
  v.Y = y;
  return v;
}

vec2 vec2_zero() {
  vec2 v;
  v.X = 0;
  v.Y = 0;
  return v;
}

bool vec2_is_zero(vec2 v) {
  return (v.X == 0 && v.Y == 0);
}
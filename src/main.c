#include "cam/cam.h"
#include <time.h>

int main() {
  vec4 v = vec4_make(1.0f, 2.0f, 3.0f, 4.0f);
  v = vec4_scale(&v, 2.0f);

  printf("(%.2f, %.2f, %.2f, %.2f)", vec4_getx(&v), vec4_gety(&v), vec4_getz(&v), vec4_getw(&v));

  return 0;
}
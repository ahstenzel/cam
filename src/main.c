#include "cam/cam.h"
#include <time.h>

void vec2_print(vec2 v) {
  printf("|%.2f|\n|%.2f|\n", vec2_getx(&v), vec2_gety(&v));
}

void vec3_print(vec3 v) {
  printf("|%.2f|\n|%.2f|\n|%.2f|\n", vec3_getx(&v), vec3_gety(&v), vec3_getz(&v));
}

void vec4_print(vec4 v) {
  printf("|%.2f|\n|%.2f|\n|%.2f|\n|%.2f|\n", vec4_getx(&v), vec4_gety(&v), vec4_getz(&v), vec4_getw(&v));
}

void mat2x2_print(mat2x2 m) {
  printf("|%.2f %.2f|\n|%.2f %.2f|\n", mat2x2_get(0, 0, &m), mat2x2_get(1, 0, &m), mat2x2_get(0, 1, &m), mat2x2_get(1, 1, &m));
}

int main() {
  mat2x2 a = mat2x2_make(1.0f, 2.0f, 3.0f, 4.0f);
  float d = mat2x2_det(&a);
  printf("%.2f", d);

  return 0;
}
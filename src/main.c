#include "cam/cam.h"
#include <time.h>

void vec2_print(vec2 v) {
  printf("(%.2f, %.2f)\n", vec2_getx(&v), vec2_gety(&v));
}

int main() {
  vec2 v = vec2_make(1.0f, 1.0f);
  vec2 u = vec2_make(1.0f, 2.0f);
  vec2 w = vec2_norm(&v);

  vec2_print(w);

  return 0;
}
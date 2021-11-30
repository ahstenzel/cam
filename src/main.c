//#define CAM_LEGACY
#include "cam/cam.h"
#include <time.h>

int main() {
  vec2 v = vec2_make(1.0f, 2.0f);

  printf("%f", vec2_getx(&v));

  return 0;
}
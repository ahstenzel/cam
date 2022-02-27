#include <iostream>
#include "cam/cam.hpp"

int main() {
  cam::vec3 v;
  cam::mat4 m;
  
  if (m == cam::mat4::identity) {
    std::cout << "id" << std::endl;
  }
  std::cout << m.determinant() << std::endl;

  cam::vec2 g;
  std::cout << g.magnitude() << std::endl;
  g.x() = 1.0f;
  std::cout << g.magnitude() << std::endl;
  return 0;
}
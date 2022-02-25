#include <iostream>
#include "cam/cam.hpp"

int main() {
  cam::vec3 v;
  cam::mat4 m;
  
  if (m == cam::mat4::identity) {
    std::cout << "id" << std::endl;
  }
  std::cout << m.determinant() << std::endl;
  return 0;
}
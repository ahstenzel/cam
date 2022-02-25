#pragma once
/*
 * mat3x3.hpp
 * Declaration for 3x3 matrix of floats in column-major order.
 */

#include "cam/linear/linear.hpp"
#include "cam/linear/mat2.hpp"
#include "cam/linear/vec3.hpp"

namespace cam {
  class mat3 {
  private:
    float det_;
    float data_[9];
  
  public:
    // Default constructor
    mat3(float x1 = 1.0f, float y1 = 0.0f, float z1 = 0.0f, 
         float x2 = 0.0f, float y2 = 1.0f, float z2 = 0.0f, 
         float x3 = 0.0f, float y3 = 0.0f, float z3 = 1.0f);

    // Copy constructor
    mat3(const mat3& copy);

    // Move constructor
    mat3(mat3&& move) noexcept;

    // Destructor
    ~mat3();

    // Assignment
    mat3& operator=(const mat3& other);
    mat3& operator=(mat3&& move) noexcept;

    // Comparison
    bool operator!=(const mat3& rhs) const;
    bool operator==(const mat3& rhs) const;

    // Arithmetic
    mat3& operator+=(const mat3& rhs);
    friend mat3 operator+(mat3 lhs, const mat3& rhs);
    mat3& operator-=(const mat3& rhs);
    friend mat3 operator-(mat3 lhs, const mat3& rhs);
    mat3& operator*=(const mat3& rhs);
    friend mat3 operator*(mat3 lhs, const mat3& rhs);
    mat3& operator*=(const float& rhs);
    friend mat3 operator*(mat3 lhs, const float& rhs);
    friend mat3 operator*(const float& rhs, mat3 lhs);
    friend vec3 operator*(mat3 lhs, const vec3& rhs);

    // Element access
    float& at(std::size_t row, std::size_t col);
    const float& at(std::size_t row, std::size_t col) const;

    // Get the determinant of this matrix
    float determinant();

    // Swap the contents with the other matrix
    void swap(mat3& other) noexcept;

    // Create a smaller matrix by removing the given row and column
    mat2 submatrix(std::size_t row, std::size_t col);

    // Identity matrix
    const static mat3 identity;
  };
}
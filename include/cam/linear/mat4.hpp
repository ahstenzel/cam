#pragma once
/*
 * mat4x4.hpp
 * Declaration for 4x4 matrix of floats in column-major order.
 */

#include "cam/linear/linear.hpp"
#include "cam/linear/mat3.hpp"
#include "cam/linear/vec4.hpp"

namespace cam {
  class mat4 {
  private:
    float det_;
    float data_[16];
  
  public:
    // Default constructor
    mat4(float x1 = 1.0f, float y1 = 0.0f, float z1 = 0.0f, float w1 = 0.0f, 
         float x2 = 0.0f, float y2 = 1.0f, float z2 = 0.0f, float w2 = 0.0f,
         float x3 = 0.0f, float y3 = 0.0f, float z3 = 1.0f, float w3 = 0.0f, 
         float x4 = 0.0f, float y4 = 0.0f, float z4 = 0.0f, float w4 = 1.0f);

    // Copy constructor
    mat4(const mat4& copy);

    // Move constructor
    mat4(mat4&& move) noexcept;

    // Destructor
    ~mat4();

    // Assignment
    mat4& operator=(const mat4& other);
    mat4& operator=(mat4&& move) noexcept;

    // Comparison
    bool operator!=(const mat4& rhs) const;
    bool operator==(const mat4& rhs) const;

    // Arithmetic
    mat4& operator+=(const mat4& rhs);
    friend mat4 operator+(mat4 lhs, const mat4& rhs);
    mat4& operator-=(const mat4& rhs);
    friend mat4 operator-(mat4 lhs, const mat4& rhs);
    mat4& operator*=(const mat4& rhs);
    friend mat4 operator*(mat4 lhs, const mat4& rhs);
    mat4& operator*=(const float& rhs);
    friend mat4 operator*(mat4 lhs, const float& rhs);
    friend mat4 operator*(const float& rhs, mat4 lhs);
    friend vec4 operator*(mat4 lhs, const vec4& rhs);

    // Element access
    float& at(std::size_t row, std::size_t col);
    const float& at(std::size_t row, std::size_t col) const;

    // Get the determinant of this matrix
    float determinant();

    // Swap the contents with the other matrix
    void swap(mat4& other) noexcept;

    // Create a smaller matrix by removing the given row and column
    mat3 submatrix(std::size_t row, std::size_t col);

    // Identity matrix
    const static mat4 identity;
  };
}
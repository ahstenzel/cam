#pragma once
/*
 * mat2x2.hpp
 * Declaration for 2x2 matrix of floats in column-major order.
 */

#include "cam/linear/linear.hpp"
#include "cam/linear/vec2.hpp"

namespace cam {
  class mat2 {
  private:
    float det_;
    float data_[4];
  
  public:
    // Default constructor
    mat2(float x1 = 1.0f, float y1 = 0.0f, float x2 = 0.0f, float y2 = 1.0f);

    // Copy constructor
    mat2(const mat2& copy);

    // Move constructor
    mat2(mat2&& move) noexcept;

    // Destructor
    ~mat2();

    // Assignment
    mat2& operator=(const mat2& other);
    mat2& operator=(mat2&& move) noexcept;

    // Comparison
    bool operator!=(const mat2& rhs) const;
    bool operator==(const mat2& rhs) const;

    // Arithmetic
    mat2& operator+=(const mat2& rhs);
    friend mat2 operator+(mat2 lhs, const mat2& rhs);
    mat2& operator-=(const mat2& rhs);
    friend mat2 operator-(mat2 lhs, const mat2& rhs);
    mat2& operator*=(const mat2& rhs);
    friend mat2 operator*(mat2 lhs, const mat2& rhs);
    mat2& operator*=(const float& rhs);
    friend mat2 operator*(mat2 lhs, const float& rhs);
    friend mat2 operator*(const float& rhs, mat2 lhs);
    friend vec2 operator*(mat2 lhs, const vec2& rhs);

    // Element access
    float& at(std::size_t row, std::size_t col);
    const float& at(std::size_t row, std::size_t col) const;

    // Get the determinant of this matrix
    float determinant();

    // Swap the contents with the other matrix
    void swap(mat2& other) noexcept;

    // Identity matrix
    const static mat2 identity;
  };
}
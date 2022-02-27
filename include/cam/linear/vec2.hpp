#pragma once
/*
 * vec2.hpp
 * Declaration for 2D vector of floats.
 */

#include "cam/linear/linear.hpp"

namespace cam {
  class vec2 {
  private:
    float mag_;
    float data_[2];
  
  public:
    // Default constructor
    vec2(float x = 0.0f, float y = 0.0f);
    
    // Copy constructor
    vec2(const vec2& v);
    
    // Move constructor
    vec2(vec2&& v) noexcept;
    
    // Destructor
    ~vec2();
    
    // Assignment
    vec2& operator=(const vec2& other);
    vec2& operator=(vec2&& move) noexcept;

    // Comparison
    bool operator!=(const vec2& rhs) const;
    bool operator==(const vec2& rhs) const;

    // Arithmetic
    vec2& operator+=(const vec2& rhs);
    friend vec2 operator+(vec2 lhs, const vec2& rhs);
    vec2& operator-=(const vec2& rhs);
    friend vec2 operator-(vec2 lhs, const vec2& rhs);
    vec2& operator*=(const vec2& rhs);
    friend vec2 operator*(vec2 lhs, const vec2& rhs);
    vec2& operator/=(const vec2& rhs);
    friend vec2 operator/(vec2 lhs, const vec2& rhs);
    vec2& operator*=(const float& rhs);
    friend vec2 operator*(vec2 lhs, const float& rhs);
    friend vec2 operator*(const float& lhs, vec2 rhs);
    vec2& operator/=(const float& rhs);
    friend vec2 operator/(vec2 lhs, const float& rhs);
    friend vec2 operator/(const float& lhs, vec2 rhs);

    // Element access
    float& x();
    const float& x() const;
    float& y();
    const float& y() const;

    // Get the magnitude of this vector
    float magnitude();
    
    // Swap the contents with the other vector
    void swap(vec2& other) noexcept;

    // Normalize this vector
    vec2 normalize();

    // Sum all the components of the vector
    float sum();

    // Zero vector
    const static vec2 zero;

    // Calculate the distance between two vectors
    static vec2 distance(const vec2& a, const vec2& b);

    // Calculate the dot product of two vectors
    static float dot_product(const vec2& a, const vec2& b);
  };
}

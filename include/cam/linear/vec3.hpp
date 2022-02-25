#pragma once
/*
 * vec3.hpp
 * Declaration for 3D vector of floats.
 */

#include "cam/linear/linear.hpp"

namespace cam {
  class vec3 {
  private:
    float mag_;
    float data_[3];
  
  public:
    // Default constructor
    vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    
    // Copy constructor
    vec3(const vec3& v);
    
    // Move constructor
    vec3(vec3&& v) noexcept;
    
    // Destructor
    ~vec3();
    
    // Assignment
    vec3& operator=(const vec3& other);
    vec3& operator=(vec3&& move) noexcept;

    // Comparison
    bool operator!=(const vec3& rhs) const;
    bool operator==(const vec3& rhs) const;

    // Arithmetic
    vec3& operator+=(const vec3& rhs);
    friend vec3 operator+(vec3 lhs, const vec3& rhs);
    vec3& operator-=(const vec3& rhs);
    friend vec3 operator-(vec3 lhs, const vec3& rhs);
    vec3& operator*=(const vec3& rhs);
    friend vec3 operator*(vec3 lhs, const vec3& rhs);
    vec3& operator/=(const vec3& rhs);
    friend vec3 operator/(vec3 lhs, const vec3& rhs);
    vec3& operator*=(const float& rhs);
    friend vec3 operator*(vec3 lhs, const float& rhs);
    friend vec3 operator*(const float& lhs, vec3 rhs);
    vec3& operator/=(const float& rhs);
    friend vec3 operator/(vec3 lhs, const float& rhs);
    friend vec3 operator/(const float& lhs, vec3 rhs);

    // Element access
    float& x();
    const float& x() const;
    float& y();
    const float& y() const;
    float& z();
    const float& z() const;

    // Get the magnitude of this vector
    float magnitude();
    
    // Swap the contents with the other vector
    void swap(vec3& other) noexcept;

    // Normalize this vector
    vec3 normalize();

    // Zero vector
    const static vec3 zero;
  };

  float dot_product(const vec3& a, const vec3& b);

  vec3 cross_product(const vec3& a, const vec3& b);
}

#pragma once
/*
 * vec4.hpp
 * Declaration for 4D vector of floats.
 */

#include "cam/linear/linear.hpp"

namespace cam {
  class vec4 {
  private:
    float mag_;
    float data_[4];
  
  public:
    // Default constructor
    vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
    
    // Copy constructor
    vec4(const vec4& v);
    
    // Move constructor
    vec4(vec4&& v) noexcept;
    
    // Destructor
    ~vec4();
    
    // Assignment
    vec4& operator=(const vec4& other);
    vec4& operator=(vec4&& move) noexcept;

    // Comparison
    bool operator!=(const vec4& rhs) const;
    bool operator==(const vec4& rhs) const;

    // Arithmetic
    vec4& operator+=(const vec4& rhs);
    friend vec4 operator+(vec4 lhs, const vec4& rhs);
    vec4& operator-=(const vec4& rhs);
    friend vec4 operator-(vec4 lhs, const vec4& rhs);
    vec4& operator*=(const vec4& rhs);
    friend vec4 operator*(vec4 lhs, const vec4& rhs);
    vec4& operator/=(const vec4& rhs);
    friend vec4 operator/(vec4 lhs, const vec4& rhs);
    vec4& operator*=(const float& rhs);
    friend vec4 operator*(vec4 lhs, const float& rhs);
    friend vec4 operator*(const float& lhs, vec4 rhs);
    vec4& operator/=(const float& rhs);
    friend vec4 operator/(vec4 lhs, const float& rhs);
    friend vec4 operator/(const float& lhs, vec4 rhs);

    // Element access
    float& x();
    const float& x() const;
    float& y();
    const float& y() const;
    float& z();
    const float& z() const;
    float& w();
    const float& w() const;

    // Get the magnitude of this vector
    float magnitude();
    
    // Swap the contents with the other vector
    void swap(vec4& other) noexcept;

    // Normalize this vector
    vec4 normalize();

    // Sum all the components of the vector
    float sum();

    // Zero vector
    const static vec4 zero;

    // Calculate the distance between two vectors
    static vec4 distance(const vec4& a, const vec4& b);

    // Calculate the dot product of two vectors
    static float dot_product(const vec4& a, const vec4& b);
  };
}

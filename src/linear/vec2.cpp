/*
 * vec2.cpp
 * Declaration for 2D vector of floats.
 */

#include "cam/linear/vec2.hpp"

namespace cam {
  vec2::vec2(float x, float y) :
    data_{x, y}, mag_(-1.0f)
    {}
  
  vec2::vec2(const vec2& copy) :
    data_{copy.data_[0], copy.data_[1]}, mag_(copy.mag_)
    {}
  
  vec2::vec2(vec2&& move) noexcept :
    data_{0.0f, 0.0f}, mag_(-1.0f) {
      move.swap(*this);
    }
  
  vec2::~vec2() 
    {}
  
  vec2& vec2::operator=(const vec2& other) {
    data_[0] = other.data_[0];
    data_[1] = other.data_[1];
    mag_ = other.mag_;
    return *this;
  }
  vec2& vec2::operator=(vec2&& move) noexcept {
    move.swap(*this);
    return *this;
  }

  bool vec2::operator!=(const vec2& rhs) const { return !(*this == rhs); }
  bool vec2::operator==(const vec2& rhs) const { 
    return (data_[0] == rhs.data_[0] && data_[1] == rhs.data_[1]); 
  }

  vec2& vec2::operator+=(const vec2& rhs) { 
    data_[0] += rhs.data_[0];
    data_[1] += rhs.data_[1];
    mag_ = -1.0f;
    return *this;
  }
  vec2 operator+(vec2 lhs, const vec2& rhs) {
    lhs += rhs;
    return lhs;
  }
  vec2& vec2::operator-=(const vec2& rhs) { 
    data_[0] -= rhs.data_[0];
    data_[1] -= rhs.data_[1];
    mag_ = -1.0f;
    return *this;
  }
  vec2 operator-(vec2 lhs, const vec2& rhs) {
    lhs -= rhs;
    return lhs;
  }
  vec2& vec2::operator*=(const vec2& rhs) {
    data_[0] *= rhs.data_[0];
    data_[1] *= rhs.data_[1];
    mag_ = -1.0f;
    return *this;
  }
  vec2 operator*(vec2 lhs, const vec2& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec2& vec2::operator/=(const vec2& rhs) {
    data_[0] /= rhs.data_[0];
    data_[1] /= rhs.data_[1];
    mag_ = -1.0f;
    return *this;
  }
  vec2 operator/(vec2 lhs, const vec2& rhs) {
    lhs /= rhs;
    return lhs;
  }
  vec2& vec2::operator*=(const float& rhs) {
    data_[0] *= rhs;
    data_[1] *= rhs;
    mag_ *= abs(rhs);
    return *this;
  }
  vec2 operator*(vec2 lhs, const float& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec2 operator*(const float& lhs, vec2 rhs) {
    rhs *= lhs;
    return rhs;
  }
  vec2& vec2::operator/=(const float& rhs) {
    data_[0] /= rhs;
    data_[1] /= rhs;
    mag_ /= abs(rhs);
    return *this;
  }
  vec2 operator/(vec2 lhs, const float& rhs) {
    lhs /= rhs;
    return lhs;
  }
  vec2 operator/(const float& lhs, vec2 rhs) {
    rhs /= lhs;
    return rhs;
  }

  float& vec2::x()              { return data_[0]; }
  const float& vec2::x() const  { return data_[0]; }
  float& vec2::y()              { return data_[1]; }
  const float& vec2::y() const  { return data_[1]; }

  float vec2::magnitude() { 
    if (mag_ < 0.0f) {
      mag_ = sqrtf((data_[0] * data_[0]) + (data_[1] * data_[1]));
    }
    return mag_;
  }
  
  void vec2::swap(vec2& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(mag_, other.mag_);
  }

  vec2 vec2::normalize() {
    vec2 v(*this);
    v /= v.magnitude();
    v.mag_ = 1.0f;
    return v;
  }

  const vec2 vec2::zero = vec2();
}
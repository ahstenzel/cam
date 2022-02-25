/*
 * vec4.cpp
 * Declaration for 4D vector of floats.
 */

#include "cam/linear/vec4.hpp"

namespace cam {
  vec4::vec4(float x, float y, float z, float w) :
    data_{x, y, z, w}, mag_(-1.0f)
    {}
  
  vec4::vec4(const vec4& v) :
    data_{v.data_[0], v.data_[1], v.data_[2], v.data_[3]}, mag_(v.mag_)
    {}
  
  vec4::vec4(vec4&& v) noexcept :
    data_{0.0f, 0.0f, 0.0f, 0.0f}, mag_(-1.0f) {
      v.swap(*this);
    }
  
  vec4::~vec4() 
    {}
  
  vec4& vec4::operator=(const vec4& other) {
    data_[0] = other.data_[0];
    data_[1] = other.data_[1];
    data_[2] = other.data_[2];
    data_[3] = other.data_[3];
    mag_ = other.mag_;
    return *this;
  }
  vec4& vec4::operator=(vec4&& move) noexcept {
    move.swap(*this);
    return *this;
  }

  bool vec4::operator!=(const vec4& rhs) const { return !(*this == rhs); }
  bool vec4::operator==(const vec4& rhs) const { 
    return (data_[0] == rhs.data_[0] && data_[1] == rhs.data_[1] && 
            data_[2] == rhs.data_[2] && data_[3] == rhs.data_[3]); 
  }

  vec4& vec4::operator+=(const vec4& rhs) { 
    data_[0] += rhs.data_[0];
    data_[1] += rhs.data_[1];
    data_[2] += rhs.data_[2];
    data_[3] += rhs.data_[3];
    mag_ = -1.0f;
    return *this;
  }
  vec4 operator+(vec4 lhs, const vec4& rhs) {
    lhs += rhs;
    return lhs;
  }
  vec4& vec4::operator-=(const vec4& rhs) { 
    data_[0] -= rhs.data_[0];
    data_[1] -= rhs.data_[1];
    data_[2] -= rhs.data_[2];
    data_[3] -= rhs.data_[3];
    mag_ = -1.0f;
    return *this;
  }
  vec4 operator-(vec4 lhs, const vec4& rhs) {
    lhs -= rhs;
    return lhs;
  }
  vec4& vec4::operator*=(const vec4& rhs) {
    data_[0] *= rhs.data_[0];
    data_[1] *= rhs.data_[1];
    data_[2] *= rhs.data_[2];
    data_[3] *= rhs.data_[3];
    mag_ = -1.0f;
    return *this;
  }
  vec4 operator*(vec4 lhs, const vec4& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec4& vec4::operator/=(const vec4& rhs) {
    data_[0] /= rhs.data_[0];
    data_[1] /= rhs.data_[1];
    data_[2] /= rhs.data_[2];
    data_[3] /= rhs.data_[3];
    mag_ = -1.0f;
    return *this;
  }
  vec4 operator/(vec4 lhs, const vec4& rhs) {
    lhs /= rhs;
    return lhs;
  }
  vec4& vec4::operator*=(const float& rhs) {
    data_[0] *= rhs;
    data_[1] *= rhs;
    data_[2] *= rhs;
    data_[3] *= rhs;
    mag_ *= abs(rhs);
    return *this;
  }
  vec4 operator*(vec4 lhs, const float& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec4 operator*(const float& lhs, vec4 rhs) {
    rhs *= lhs;
    return rhs;
  }
  vec4& vec4::operator/=(const float& rhs) {
    data_[0] /= rhs;
    data_[1] /= rhs;
    data_[2] /= rhs;
    data_[3] /= rhs;
    mag_ /= abs(rhs);
    return *this;
  }
  vec4 operator/(vec4 lhs, const float& rhs) {
    lhs /= rhs;
    return lhs;
  }
  vec4 operator/(const float& lhs, vec4 rhs) {
    rhs /= lhs;
    return rhs;
  }

  float& vec4::x()              { return data_[0]; }
  const float& vec4::x() const  { return data_[0]; }
  float& vec4::y()              { return data_[1]; }
  const float& vec4::y() const  { return data_[1]; }
  float& vec4::z()              { return data_[2]; }
  const float& vec4::z() const  { return data_[2]; }
  float& vec4::w()              { return data_[3]; }
  const float& vec4::w() const  { return data_[3]; }

  float vec4::magnitude() { 
    if (mag_ < 0.0f) {
      mag_ = sqrtf((data_[0] * data_[0]) + (data_[1] * data_[1]) + 
                   (data_[2] * data_[2]) + (data_[3] * data_[3]));
    }
    return mag_;
  }
  
  void vec4::swap(vec4& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(mag_, other.mag_);
  }

  vec4 vec4::normalize() {
    vec4 v(*this);
    v /= v.magnitude();
    v.mag_ = 1.0f;
    return v;
  }

  const vec4 vec4::zero = vec4();
}
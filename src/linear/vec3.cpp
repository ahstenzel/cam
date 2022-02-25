/*
 * vec3.cpp
 * Declaration for 3D vector of floats.
 */

#include "cam/linear/vec3.hpp"

namespace cam {
  vec3::vec3(float x, float y, float z) :
    data_{x, y, z}, mag_(-1.0f)
    {}
  
  vec3::vec3(const vec3& v) :
    data_{v.data_[0], v.data_[1], v.data_[2]}, mag_(v.mag_)
    {}
  
  vec3::vec3(vec3&& v) noexcept :
    data_{0.0f, 0.0f, 0.0f}, mag_(-1.0f) {
      v.swap(*this);
    }
  
  vec3::~vec3() 
    {}
  
  vec3& vec3::operator=(const vec3& other) {
    data_[0] = other.data_[0];
    data_[1] = other.data_[1];
    data_[2] = other.data_[2];
    mag_ = other.mag_;
    return *this;
  }
  vec3& vec3::operator=(vec3&& move) noexcept {
    move.swap(*this);
    return *this;
  }

  bool vec3::operator!=(const vec3& rhs) const { return !(*this == rhs); }
  bool vec3::operator==(const vec3& rhs) const { 
    return (data_[0] == rhs.data_[0] && data_[1] == rhs.data_[1] && data_[2] == rhs.data_[2]); 
  }

  vec3& vec3::operator+=(const vec3& rhs) { 
    data_[0] += rhs.data_[0];
    data_[1] += rhs.data_[1];
    data_[2] += rhs.data_[2];
    mag_ = -1.0f;
    return *this;
  }
  vec3 operator+(vec3 lhs, const vec3& rhs) {
    lhs += rhs;
    return lhs;
  }
  vec3& vec3::operator-=(const vec3& rhs) { 
    data_[0] -= rhs.data_[0];
    data_[1] -= rhs.data_[1];
    data_[2] -= rhs.data_[2];
    mag_ = -1.0f;
    return *this;
  }
  vec3 operator-(vec3 lhs, const vec3& rhs) {
    lhs -= rhs;
    return lhs;
  }
  vec3& vec3::operator*=(const vec3& rhs) {
    data_[0] *= rhs.data_[0];
    data_[1] *= rhs.data_[1];
    data_[2] *= rhs.data_[2];
    mag_ = -1.0f;
    return *this;
  }
  vec3 operator*(vec3 lhs, const vec3& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec3& vec3::operator/=(const vec3& rhs) {
    data_[0] /= rhs.data_[0];
    data_[1] /= rhs.data_[1];
    data_[2] /= rhs.data_[2];
    mag_ = -1.0f;
    return *this;
  }
  vec3 operator/(vec3 lhs, const vec3& rhs) {
    lhs /= rhs;
    return lhs;
  }
  vec3& vec3::operator*=(const float& rhs) {
    data_[0] *= rhs;
    data_[1] *= rhs;
    data_[2] *= rhs;
    mag_ *= abs(rhs);
    return *this;
  }
  vec3 operator*(vec3 lhs, const float& rhs) {
    lhs *= rhs;
    return lhs;
  }
  vec3 operator*(const float& lhs, vec3 rhs) {
    rhs *= lhs;
    return rhs;
  }
  vec3& vec3::operator/=(const float& rhs) {
    data_[0] /= rhs;
    data_[1] /= rhs;
    data_[2] /= rhs;
    mag_ /= abs(rhs);
    return *this;
  }
  vec3 operator/(vec3 lhs, const float& rhs) {
    lhs /= rhs;
    return lhs;
  }
  vec3 operator/(const float& lhs, vec3 rhs) {
    rhs /= lhs;
    return rhs;
  }

  float& vec3::x()              { return data_[0]; }
  const float& vec3::x() const  { return data_[0]; }
  float& vec3::y()              { return data_[1]; }
  const float& vec3::y() const  { return data_[1]; }
  float& vec3::z()              { return data_[2]; }
  const float& vec3::z() const  { return data_[2]; }

  float vec3::magnitude() { 
    if (mag_ < 0.0f) {
      mag_ = sqrtf((data_[0] * data_[0]) + (data_[1] * data_[1]) + (data_[2] * data_[2]));
    }
    return mag_;
  }
  
  void vec3::swap(vec3& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(mag_, other.mag_);
  }

  vec3 vec3::normalize() {
    vec3 v(*this);
    v /= v.magnitude();
    v.mag_ = 1.0f;
    return v;
  }

  float dot_product(const vec3& a, const vec3& b) {
    return (a.x() * b.x()) + (a.y() * b.y()) + (a.z() * b.z());
  }

  vec3 cross_product(const vec3& a, const vec3& b) {
    vec3 v;
    v.x() = (a.y() * b.z()) - (a.z() - b.y());
    v.y() = (a.z() * b.x()) - (a.x() - b.z());
    v.z() = (a.x() * b.y()) - (a.y() - b.x());
    return v;
  }

  const vec3 vec3::zero = vec3();
}
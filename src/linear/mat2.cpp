/*
 * mat2.cpp
 * Declaration for 2x2 matrix of floats in column-major order.
 */

#include "cam/linear/mat2.hpp"

namespace cam {
  mat2::mat2(float x1, float y1, float x2, float y2) :
    data_{x1, y1, x2, y2}, det_(nanf("")) 
    {}

  mat2::mat2(const mat2& copy) :
    data_{copy.data_[0], copy.data_[1], copy.data_[2], copy.data_[3]}, det_(copy.det_) 
    {}

  mat2::mat2(mat2&& move) noexcept :
    data_{0.0f, 0.0f, 0.0f, 0.0f}, det_(nanf("")) {
      move.swap(*this);
    }

  mat2::~mat2() {}

  mat2& mat2::operator=(const mat2& other) {
    data_[0] = other.data_[0];
    data_[1] = other.data_[1];
    data_[2] = other.data_[2];
    data_[3] = other.data_[3];
    det_ = other.det_;
    return *this;
  }
  mat2& mat2::operator=(mat2&& move) noexcept {
    move.swap(*this);
    return *this;
  }

  bool mat2::operator!=(const mat2& rhs) const { return !(*this == rhs); }
  bool mat2::operator==(const mat2& rhs) const {
    return (data_[0] == rhs.data_[0] &&
            data_[1] == rhs.data_[1] &&
            data_[2] == rhs.data_[2] &&
            data_[3] == rhs.data_[3]);
  }

  mat2& mat2::operator+=(const mat2& rhs) {
    data_[0] += rhs.data_[0];
    data_[1] += rhs.data_[1];
    data_[2] += rhs.data_[2];
    data_[3] += rhs.data_[3];
    det_ = nanf("");
    return *this;
  }
  mat2 operator+(mat2 lhs, const mat2& rhs) {
    lhs += rhs;
    return lhs;
  }
  mat2& mat2::operator-=(const mat2& rhs) {
    data_[0] -= rhs.data_[0];
    data_[1] -= rhs.data_[1];
    data_[2] -= rhs.data_[2];
    data_[3] -= rhs.data_[3];
    det_ = nanf("");
    return *this;
  }
  mat2 operator-(mat2 lhs, const mat2& rhs) {
    lhs -= rhs;
    return lhs;
  }
  mat2& mat2::operator*=(const mat2& rhs) {
    data_[0] = (data_[0]*rhs.data_[0]) + (data_[2]*rhs.data_[1]);
    data_[1] = (data_[1]*rhs.data_[0]) + (data_[3]*rhs.data_[1]);

    data_[2] = (data_[0]*rhs.data_[2]) + (data_[2]*rhs.data_[3]);
    data_[3] = (data_[1]*rhs.data_[2]) + (data_[3]*rhs.data_[3]);
    det_ = nanf("");
    return *this;
  }
  mat2 operator*(mat2 lhs, const mat2& rhs) {
    lhs *= rhs;
    return lhs;
  }
  mat2& mat2::operator*=(const float& rhs) {
    data_[0] *= rhs;
    data_[1] *= rhs;
    data_[2] *= rhs;
    data_[3] *= rhs;
    det_ = nanf("");
    return *this;
  }
  mat2 operator*(mat2 lhs, const float& rhs) {
    lhs *= rhs;
    return lhs;
  }
  mat2 operator*(const float& rhs, mat2 lhs) {
    lhs *= rhs;
    return lhs;
  }
  vec2 operator*(mat2 lhs, const vec2& rhs) {
    vec2 v;
    v.x() = (lhs.data_[0] * rhs.x()) + (lhs.data_[2] * rhs.y());
    v.y() = (lhs.data_[1] * rhs.x()) + (lhs.data_[3] * rhs.y());
    return v;
  }

  float& mat2::at(std::size_t row, std::size_t col)             { return data_[(col * 2) + row]; }
  const float& mat2::at(std::size_t row, std::size_t col) const { return data_[(col * 2) + row] ; }

  float mat2::determinant() {
    if (isnan(det_)) {
      det_ = (data_[0]*data_[3]) - (data_[1]*data_[2]);
    }
    return det_;
  }

  void mat2::swap(mat2& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(det_, other.det_);
  }

  const mat2 mat2::identity = mat2();
}
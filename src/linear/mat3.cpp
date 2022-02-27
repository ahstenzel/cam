/*
 * mat3.cpp
 * Declaration for 3x3 matrix of floats in column-major order.
 */

#include "cam/linear/mat3.hpp"

namespace cam {
  mat3::mat3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) :
    data_{x1, y1, z1, x2, y2, z2, x3, y3, z3}, det_(NAN) 
    {}

  mat3::mat3(const mat3& copy) :
    data_{copy.data_[0], copy.data_[1], copy.data_[2], 
          copy.data_[3], copy.data_[4], copy.data_[5], 
          copy.data_[6], copy.data_[7], copy.data_[8]}, det_(copy.det_) 
    {}

  mat3::mat3(mat3&& move) noexcept :
    data_{0.0f, 0.0f, 0.0f, 
          0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f}, det_(NAN) {
      move.swap(*this);
    }

  mat3::~mat3() {}

  mat3& mat3::operator=(const mat3& other) {
    data_[0] = other.data_[0];
    data_[1] = other.data_[1];
    data_[2] = other.data_[2];
    data_[3] = other.data_[3];
    data_[4] = other.data_[4];
    data_[5] = other.data_[5];
    data_[6] = other.data_[6];
    data_[7] = other.data_[7];
    data_[8] = other.data_[8];
    det_ = other.det_;
    return *this;
  }
  mat3& mat3::operator=(mat3&& move) noexcept {
    move.swap(*this);
    return *this;
  }

  bool mat3::operator!=(const mat3& rhs) const { return !(*this == rhs); }
  bool mat3::operator==(const mat3& rhs) const {
    return (data_[0] == rhs.data_[0] &&
            data_[1] == rhs.data_[1] &&
            data_[2] == rhs.data_[2] &&
            data_[3] == rhs.data_[3] &&
            data_[4] == rhs.data_[4] &&
            data_[5] == rhs.data_[5] &&
            data_[6] == rhs.data_[6] &&
            data_[7] == rhs.data_[7] &&
            data_[8] == rhs.data_[8]);
  }

  mat3& mat3::operator+=(const mat3& rhs) {
    data_[0] += rhs.data_[0];
    data_[1] += rhs.data_[1];
    data_[2] += rhs.data_[2];
    data_[3] += rhs.data_[3];
    data_[4] += rhs.data_[4];
    data_[5] += rhs.data_[5];
    data_[6] += rhs.data_[6];
    data_[7] += rhs.data_[7];
    data_[8] += rhs.data_[8];
    det_ = NAN;
    return *this;
  }
  mat3 operator+(mat3 lhs, const mat3& rhs) {
    lhs += rhs;
    return lhs;
  }
  mat3& mat3::operator-=(const mat3& rhs) {
    data_[0] -= rhs.data_[0];
    data_[1] -= rhs.data_[1];
    data_[2] -= rhs.data_[2];
    data_[3] -= rhs.data_[3];
    data_[4] -= rhs.data_[4];
    data_[5] -= rhs.data_[5];
    data_[6] -= rhs.data_[6];
    data_[7] -= rhs.data_[7];
    data_[8] -= rhs.data_[8];
    det_ = NAN;
    return *this;
  }
  mat3 operator-(mat3 lhs, const mat3& rhs) {
    lhs -= rhs;
    return lhs;
  }
  mat3& mat3::operator*=(const mat3& rhs) {
    data_[0] = (data_[0]*rhs.data_[0]) + (data_[3]*rhs.data_[1]) + (data_[6]*rhs.data_[2]);
    data_[1] = (data_[1]*rhs.data_[0]) + (data_[4]*rhs.data_[1]) + (data_[7]*rhs.data_[2]);
    data_[2] = (data_[2]*rhs.data_[0]) + (data_[5]*rhs.data_[1]) + (data_[8]*rhs.data_[2]);

    data_[3] = (data_[0]*rhs.data_[3]) + (data_[3]*rhs.data_[4]) + (data_[6]*rhs.data_[5]);
    data_[4] = (data_[1]*rhs.data_[3]) + (data_[4]*rhs.data_[4]) + (data_[7]*rhs.data_[5]);
    data_[5] = (data_[2]*rhs.data_[3]) + (data_[5]*rhs.data_[4]) + (data_[8]*rhs.data_[5]);
    
    data_[6] = (data_[0]*rhs.data_[6]) + (data_[3]*rhs.data_[7]) + (data_[6]*rhs.data_[8]);
    data_[7] = (data_[1]*rhs.data_[6]) + (data_[4]*rhs.data_[7]) + (data_[7]*rhs.data_[8]);
    data_[8] = (data_[2]*rhs.data_[6]) + (data_[5]*rhs.data_[7]) + (data_[8]*rhs.data_[8]);
    det_ = NAN;
    return *this;
  }
  mat3 operator*(mat3 lhs, const mat3& rhs) {
    lhs *= rhs;
    return lhs;
  }
  mat3& mat3::operator*=(const float& rhs) {
    data_[0] *= rhs;
    data_[1] *= rhs;
    data_[2] *= rhs;
    data_[3] *= rhs;
    data_[4] *= rhs;
    data_[5] *= rhs;
    data_[6] *= rhs;
    data_[7] *= rhs;
    data_[8] *= rhs;
    det_ = NAN;
    return *this;
  }
  mat3 operator*(mat3 lhs, const float& rhs) {
    lhs *= rhs;
    return lhs;
  }
  mat3 operator*(const float& rhs, mat3 lhs) {
    lhs *= rhs;
    return lhs;
  }
  vec3 operator*(mat3 lhs, const vec3& rhs) {
    return vec3(
      (lhs.data_[0] * rhs.x()) + (lhs.data_[3] * rhs.y()) + (lhs.data_[6] * rhs.z()),
      (lhs.data_[1] * rhs.x()) + (lhs.data_[4] * rhs.y()) + (lhs.data_[7] * rhs.z()),
      (lhs.data_[2] * rhs.x()) + (lhs.data_[5] * rhs.y()) + (lhs.data_[8] * rhs.z())
    );
  }

  float& mat3::at(std::size_t row, std::size_t col)             { det_ = NAN; return data_[(col * 3) + row]; }
  const float& mat3::at(std::size_t row, std::size_t col) const { return data_[(col * 3) + row] ; }

  float mat3::determinant() {
    if (isnan(det_)) {
      det_ = 0.0f;

      mat2 n = submatrix(0, 0);
      det_ += data_[0] * n.determinant();

      n = submatrix(0, 1);
      det_ -= data_[3] * n.determinant();

      n = submatrix(0, 2);
      det_ += data_[6] * n.determinant();
    }
    return det_;
  }

  void mat3::swap(mat3& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(det_, other.det_);
  }

  mat2 mat3::submatrix(std::size_t row, std::size_t col) {
    std::size_t ind_0 = 0;
    if (row == (ind_0 % 3)) { ind_0 += 1; }
    if (col == (ind_0 / 3)) { ind_0 += 3; }

    std::size_t ind_1 = ind_0 + 1;
    if (row == (ind_1 % 3)) { ind_1 += 1; }
    if (col == (ind_1 / 3)) { ind_1 += 3; }
    
    std::size_t ind_2 = ind_0 + 3;
    if (row == (ind_2 % 3)) { ind_2 += 1; }
    if (col == (ind_2 / 3)) { ind_2 += 3; }
    
    std::size_t ind_3 = ind_2 + 1;
    if (row == (ind_3 % 3)) { ind_3 += 1; }
    if (col == (ind_3 / 3)) { ind_3 += 3; }

    return mat2(data_[ind_0], data_[ind_1], data_[ind_2], data_[ind_3]);
  }

  const mat3 mat3::identity = mat3();
}
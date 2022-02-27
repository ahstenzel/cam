/*
 * mat4.cpp
 * Declaration for 4x4 matrix of floats in column-major order.
 */

#include "cam/linear/mat4.hpp"

namespace cam {
  mat4::mat4(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2,
             float x3, float y3, float z3, float w3, float x4, float y4, float z4, float w4) :
             data_{x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4}, det_(NAN) {}

  mat4::mat4(const mat4& copy) :
    data_{copy.data_[0],  copy.data_[1],  copy.data_[2],  copy.data_[3], 
          copy.data_[4],  copy.data_[5],  copy.data_[6],  copy.data_[7], 
          copy.data_[8],  copy.data_[9],  copy.data_[10], copy.data_[11], 
          copy.data_[12], copy.data_[13], copy.data_[14], copy.data_[15]}, det_(copy.det_) {}

  mat4::mat4(mat4&& move) noexcept :
    data_{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, det_(NAN) {
      move.swap(*this);
    }

  mat4::~mat4() {}

  mat4& mat4::operator=(const mat4& other) {
    data_[0] = other.data_[0];
    data_[1] = other.data_[1];
    data_[2] = other.data_[2];
    data_[3] = other.data_[3];
    data_[4] = other.data_[4];
    data_[5] = other.data_[5];
    data_[6] = other.data_[6];
    data_[7] = other.data_[7];
    data_[8] = other.data_[8];
    data_[9] = other.data_[9];
    data_[10] = other.data_[10];
    data_[11] = other.data_[11];
    data_[12] = other.data_[12];
    data_[13] = other.data_[13];
    data_[14] = other.data_[14];
    data_[15] = other.data_[15];
    det_ = other.det_;
    return *this;
  }
  mat4& mat4::operator=(mat4&& move) noexcept {
    move.swap(*this);
    return *this;
  }

  bool mat4::operator!=(const mat4& rhs) const { return !(*this == rhs); }
  bool mat4::operator==(const mat4& rhs) const {
    return (data_[0] == rhs.data_[0] &&
            data_[1] == rhs.data_[1] &&
            data_[2] == rhs.data_[2] &&
            data_[3] == rhs.data_[3] &&
            data_[4] == rhs.data_[4] &&
            data_[5] == rhs.data_[5] &&
            data_[6] == rhs.data_[6] &&
            data_[7] == rhs.data_[7] &&
            data_[8] == rhs.data_[8] &&
            data_[9] == rhs.data_[9] &&
            data_[10] == rhs.data_[10] &&
            data_[11] == rhs.data_[11] &&
            data_[12] == rhs.data_[12] &&
            data_[13] == rhs.data_[13] &&
            data_[14] == rhs.data_[14] &&
            data_[15] == rhs.data_[15]);
  }

  mat4& mat4::operator+=(const mat4& rhs) {
    data_[0] += rhs.data_[0];
    data_[1] += rhs.data_[1];
    data_[2] += rhs.data_[2];
    data_[3] += rhs.data_[3];
    data_[4] += rhs.data_[4];
    data_[5] += rhs.data_[5];
    data_[6] += rhs.data_[6];
    data_[7] += rhs.data_[7];
    data_[8] += rhs.data_[8];
    data_[9] += rhs.data_[9];
    data_[10] += rhs.data_[10];
    data_[11] += rhs.data_[11];
    data_[12] += rhs.data_[12];
    data_[13] += rhs.data_[13];
    data_[14] += rhs.data_[14];
    data_[15] += rhs.data_[15];
    det_ = NAN;
    return *this;
  }
  mat4 operator+(mat4 lhs, const mat4& rhs) {
    lhs += rhs;
    return lhs;
  }
  mat4& mat4::operator-=(const mat4& rhs) {
    data_[0] -= rhs.data_[0];
    data_[1] -= rhs.data_[1];
    data_[2] -= rhs.data_[2];
    data_[3] -= rhs.data_[3];
    data_[4] -= rhs.data_[4];
    data_[5] -= rhs.data_[5];
    data_[6] -= rhs.data_[6];
    data_[7] -= rhs.data_[7];
    data_[8] -= rhs.data_[8];
    data_[9] -= rhs.data_[9];
    data_[10] -= rhs.data_[10];
    data_[11] -= rhs.data_[11];
    data_[12] -= rhs.data_[12];
    data_[13] -= rhs.data_[13];
    data_[14] -= rhs.data_[14];
    data_[15] -= rhs.data_[15];
    det_ = NAN;
    return *this;
  }
  mat4 operator-(mat4 lhs, const mat4& rhs) {
    lhs -= rhs;
    return lhs;
  }
  mat4& mat4::operator*=(const mat4& rhs) {
    data_[0] = (data_[0]*rhs.data_[0]) + (data_[4]*rhs.data_[1]) + (data_[8]*rhs.data_[2])  + (data_[12]*rhs.data_[3]);
    data_[1] = (data_[1]*rhs.data_[0]) + (data_[5]*rhs.data_[1]) + (data_[9]*rhs.data_[2])  + (data_[13]*rhs.data_[3]);
    data_[2] = (data_[2]*rhs.data_[0]) + (data_[6]*rhs.data_[1]) + (data_[10]*rhs.data_[2]) + (data_[14]*rhs.data_[3]);
    data_[3] = (data_[3]*rhs.data_[0]) + (data_[7]*rhs.data_[1]) + (data_[11]*rhs.data_[2]) + (data_[15]*rhs.data_[3]);

    data_[4] = (data_[0]*rhs.data_[4]) + (data_[4]*rhs.data_[5]) + (data_[8]*rhs.data_[6])  + (data_[12]*rhs.data_[7]);
    data_[5] = (data_[1]*rhs.data_[4]) + (data_[5]*rhs.data_[5]) + (data_[9]*rhs.data_[6])  + (data_[13]*rhs.data_[7]);
    data_[6] = (data_[2]*rhs.data_[4]) + (data_[6]*rhs.data_[5]) + (data_[10]*rhs.data_[6]) + (data_[14]*rhs.data_[7]);
    data_[7] = (data_[3]*rhs.data_[4]) + (data_[7]*rhs.data_[5]) + (data_[11]*rhs.data_[6]) + (data_[15]*rhs.data_[7]);

    data_[8]  = (data_[0]*rhs.data_[8]) + (data_[4]*rhs.data_[9]) + (data_[8]*rhs.data_[10])  + (data_[12]*rhs.data_[11]);
    data_[9]  = (data_[1]*rhs.data_[8]) + (data_[5]*rhs.data_[9]) + (data_[9]*rhs.data_[10])  + (data_[13]*rhs.data_[11]);
    data_[10] = (data_[2]*rhs.data_[8]) + (data_[6]*rhs.data_[9]) + (data_[10]*rhs.data_[10]) + (data_[14]*rhs.data_[11]);
    data_[11] = (data_[3]*rhs.data_[8]) + (data_[7]*rhs.data_[9]) + (data_[11]*rhs.data_[10]) + (data_[15]*rhs.data_[11]);

    data_[12] = (data_[0]*rhs.data_[12]) + (data_[4]*rhs.data_[13]) + (data_[8]*rhs.data_[14])  + (data_[12]*rhs.data_[15]);
    data_[13] = (data_[1]*rhs.data_[12]) + (data_[5]*rhs.data_[13]) + (data_[9]*rhs.data_[14])  + (data_[13]*rhs.data_[15]);
    data_[14] = (data_[2]*rhs.data_[12]) + (data_[6]*rhs.data_[13]) + (data_[10]*rhs.data_[14]) + (data_[14]*rhs.data_[15]);
    data_[15] = (data_[3]*rhs.data_[12]) + (data_[7]*rhs.data_[13]) + (data_[11]*rhs.data_[14]) + (data_[15]*rhs.data_[15]);
    det_ = NAN;
    return *this;
  }
  mat4 operator*(mat4 lhs, const mat4& rhs) {
    lhs *= rhs;
    return lhs;
  }
  mat4& mat4::operator*=(const float& rhs) {
    data_[0] *= rhs;
    data_[1] *= rhs;
    data_[2] *= rhs;
    data_[3] *= rhs;
    data_[4] *= rhs;
    data_[5] *= rhs;
    data_[6] *= rhs;
    data_[7] *= rhs;
    data_[8] *= rhs;
    data_[9] *= rhs;
    data_[10] *= rhs;
    data_[11] *= rhs;
    data_[12] *= rhs;
    data_[13] *= rhs;
    data_[14] *= rhs;
    data_[15] *= rhs;
    det_ = NAN;
    return *this;
  }
  mat4 operator*(mat4 lhs, const float& rhs) {
    lhs *= rhs;
    return lhs;
  }
  mat4 operator*(const float& rhs, mat4 lhs) {
    lhs *= rhs;
    return lhs;
  }
  vec4 operator*(mat4 lhs, const vec4& rhs) {
    return vec4(
      (lhs.data_[0] * rhs.x()) + (lhs.data_[4] * rhs.y()) + (lhs.data_[8] * rhs.z())  + (lhs.data_[12] * rhs.w()),
      (lhs.data_[1] * rhs.x()) + (lhs.data_[5] * rhs.y()) + (lhs.data_[9] * rhs.z())  + (lhs.data_[13] * rhs.w()),
      (lhs.data_[2] * rhs.x()) + (lhs.data_[6] * rhs.y()) + (lhs.data_[10] * rhs.z()) + (lhs.data_[14] * rhs.w()),
      (lhs.data_[3] * rhs.x()) + (lhs.data_[7] * rhs.y()) + (lhs.data_[11] * rhs.z()) + (lhs.data_[15] * rhs.w())
    );
  }

  float& mat4::at(std::size_t row, std::size_t col)             { det_ = NAN; return data_[(col * 4) + row]; }
  const float& mat4::at(std::size_t row, std::size_t col) const { return data_[(col * 4) + row] ; }

  float mat4::determinant() {
    if (isnan(det_)) {
      det_ = 0.0f;

      mat3 n = submatrix(0, 0);
      det_ += data_[0] * n.determinant();

      n = submatrix(0, 1);
      det_ -= data_[4] * n.determinant();

      n = submatrix(0, 2);
      det_ += data_[8] * n.determinant();

      n = submatrix(0, 3);
      det_ -= data_[12] * n.determinant();
    }
    return det_;
  }

  void mat4::swap(mat4& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(det_, other.det_);
  }

  mat3 mat4::submatrix(std::size_t row, std::size_t col) {
    std::size_t ind_0 = 0;
    if (row == (ind_0 % 4)) { ind_0 += 1; }
    if (col == (ind_0 / 4)) { ind_0 += 4; }

    std::size_t ind_1 = ind_0 + 1;
    if (row == (ind_1 % 4)) { ind_1 += 1; }
    if (col == (ind_1 / 4)) { ind_1 += 4; }

    std::size_t ind_2 = ind_0 + 2;
    if (row == (ind_2 % 4)) { ind_2 += 1; }
    if (col == (ind_2 / 4)) { ind_2 += 4; }

    std::size_t ind_3 = ind_0 + 4;
    if (row == (ind_3 % 4)) { ind_3 += 1; }
    if (col == (ind_3 / 4)) { ind_3 += 4; }

    std::size_t ind_4 = ind_3 + 1;
    if (row == (ind_4 % 4)) { ind_4 += 1; }
    if (col == (ind_4 / 4)) { ind_4 += 4; }

    std::size_t ind_5 = ind_3 + 2;
    if (row == (ind_5 % 4)) { ind_5 += 1; }
    if (col == (ind_5 / 4)) { ind_5 += 4; }

    std::size_t ind_6 = ind_3 + 4;
    if (row == (ind_6 % 4)) { ind_6 += 1; }
    if (col == (ind_6 / 4)) { ind_6 += 4; }

    std::size_t ind_7 = ind_6 + 1;
    if (row == (ind_7 % 4)) { ind_7 += 1; }
    if (col == (ind_7 / 4)) { ind_7 += 4; }

    std::size_t ind_8 = ind_6 + 2;
    if (row == (ind_8 % 4)) { ind_8 += 1; }
    if (col == (ind_8 / 4)) { ind_8 += 4; }

    return mat3(data_[ind_0], data_[ind_1], data_[ind_2], 
                data_[ind_3], data_[ind_4], data_[ind_5],
                data_[ind_6], data_[ind_7], data_[ind_8]);
  }

  const mat4 mat4::identity = mat4();
}
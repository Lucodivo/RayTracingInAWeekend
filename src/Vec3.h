#pragma once

#include <math.h>

class Vec3
{
public:

  float e[3] = {0};

  // constructors
  Vec3() {}
  Vec3(float x, float y, float z) { e[0] = x; e[1] = y; e[2] = z; }

  // accessors
  inline float x() const { return e[0]; }
  inline float y() const { return e[1]; }
  inline float z() const { return e[2]; }
  inline float r() const { return e[0]; }
  inline float g() const { return e[1]; }
  inline float b() const { return e[2]; }

  inline float operator[](int i) const { return e[i]; }

  inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
  inline float lengthSquared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

  // mutators
  inline Vec3& operator+=(const Vec3 &other) {
    e[0] += other.e[0];
    e[1] += other.e[1];
    e[2] += other.e[2];
    return *this;
  }

  inline Vec3& operator+=(const float a) {
    e[0] += a;
    e[1] += a;
    e[2] += a;
    return *this;
  }

  inline Vec3& operator-=(const Vec3 &other) {
    e[0] -= other.e[0];
    e[1] -= other.e[1];
    e[2] -= other.e[2];
    return *this;
  }

  inline Vec3& operator*=(const Vec3 &other) {
    e[0] *= other.e[0];
    e[1] *= other.e[1];
    e[2] *= other.e[2];
    return *this;
  }

  inline Vec3& operator/=(const Vec3 &other) {
    e[0] /= other.e[0];
    e[1] /= other.e[1];
    e[2] /= other.e[2];
    return *this;
  }

  inline Vec3& operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  inline Vec3& operator/=(const float t) {
    float inverseT = 1.0 / t;
    e[0] *= inverseT;
    e[1] *= inverseT;
    e[2] *= inverseT;
    return *this;
  }

  inline void normalize() {
    float lengthInverse = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= lengthInverse; e[1] *= lengthInverse; e[2] *= lengthInverse;
  }

  // operations
  inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
};

inline Vec3 normalize(const Vec3 &v) {
  float lengthInverse = 1.0 / sqrt(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
  return Vec3(v.e[0] * lengthInverse, v.e[1] * lengthInverse, v.e[2] * lengthInverse);
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator+(const Vec3 &v1, const float a) {
  return Vec3(v1.e[0] + a, v1.e[1] + a, v1.e[2] + a);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(float t, const Vec3 &v) {
  return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, float t) {
  return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator/(const Vec3 &v, float t) {
  return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline float dot(const Vec3 &v1, const Vec3 &v2) {
  return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
  return Vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
              -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[1]),
              (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

// NOTE: Normal is expected to be normalized
inline Vec3 reflect(const Vec3& vec, const Vec3& normal) {
  Vec3 projVecOnNormal = dot(vec, normal) * normal;
  return vec - (2.0 * projVecOnNormal);
}
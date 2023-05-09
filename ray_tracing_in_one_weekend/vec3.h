#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
private:
  double m_e[3];

public:
  vec3(): m_e{0, 0, 0} {}
  vec3(double e0, double e1, double e2): m_e{e0, e1, e2} {}

  double x() const { return m_e[0]; }
  double y() const { return m_e[1]; }
  double z() const { return m_e[2]; }

  vec3 operator-() const { return vec3(-m_e[0], -m_e[1], -m_e[2] ); }

  inline vec3 operator*(double t) const {
    return vec3(t*m_e[0], t*m_e[1], t*m_e[2]);
  }

  double operator[](int i) const
  {
    if (i < 0 || i >= 3) {
      throw std::out_of_range("Index out of range");
    }
    return m_e[i];
  }

  double& operator[](int i)
  {
    if (i < 0 || i >= 3) {
        throw std::out_of_range("Index out of range");
    }
    return m_e[i];
  }

  vec3& operator+=(const vec3 &v)
  {
    m_e[0] += v.m_e[0];
    m_e[1] += v.m_e[1];
    m_e[2] += v.m_e[2];
    return *this;
  }

  vec3& operator*=(double t)
  {
    m_e[0] *= t;
    m_e[1] *= t;
    m_e[2] *= t;
    return *this;
  }

  vec3& operator/=(const double t)
  {
    return *this *= 1/t;
  }

  double length() const
  {
    return sqrt(length_squared());
  }

  double length_squared() const
  {
    return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
  }

  friend inline vec3 operator*(double t, const vec3 &v);
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(double t, const vec3 &v)
{
  return vec3(t*v.x(), t*v.y(), t*v.z());
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.x() * v.x()
         + u.y() * v.y()
         + u.z() * v.z();
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif
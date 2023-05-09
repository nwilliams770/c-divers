#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
private:
  point3 m_origin;
  vec3 m_direction;

public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : m_origin(origin), m_direction(direction)
    {}

    point3 origin() const  { return m_origin; }
    vec3 direction() const { return m_direction; }

    point3 at(double t) const {
        return m_origin + t*m_direction;
    }
};

#endif
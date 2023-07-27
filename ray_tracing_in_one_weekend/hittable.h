#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct HitRecord {
    Point3 p;              // Point of intersection on the surface
    Vec3 normal;           // Normal vector at the intersection point
    double t;              // Parameter 't' indicating the intersection distance along the ray
    bool front_face;       // Flag indicating whether the ray hit the front face of the object

    // Sets the face normal based on the ray direction and outward normal
    inline void set_face_normal(const Ray& r, const Vec3& outward_normal)
    {
      // Determines if the ray is hitting the front face or the back face
      front_face = dot(r.direction(), outward_normal) < 0;
      // If hitting the front face, use the outward normal; otherwise, use the inverted outward normal
      normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
  virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};



#endif
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable
{
public:
  Point3 m_center;
  double m_radius;

  Sphere() {}
  Sphere(Point3 center, double radius): m_center(center), m_radius(radius) {};

  bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool Sphere::hit (const Ray& r, double t_min, double t_max, hit_record& rec) const
{
  // Compute the vector from the ray origin to the sphere center
  Vec3 ray_to_center = r.origin() - m_center;

  // Compute the coefficients of the quadratic equation
  auto a = r.direction().length_squared();
  auto half_b = dot(ray_to_center, r.direction());
  auto c = ray_to_center.length_squared() - m_radius * m_radius;

  // Compute the discriminant of the quadratic equation
  auto discriminant = half_b * half_b - a * c;

  // Check if the ray intersects the sphere
  if (discriminant < 0)
  {
    return false;
  }

  // Compute the square root of the discriminant for further calculations
  auto sqrtd = sqrt(discriminant);

  // Find the smallest root that lies within the acceptable range
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root)
  {
    // If the smallest root is outside the range, check the larger root
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root)
    {
      return false;
    }
  }

  // Calculate the hit record values
  rec.t = root;
  rec.p = r.at(rec.t);
  rec.normal = (rec.p - m_center) / m_radius;
  Vec3 outward_normal = (rec.p - m_center) / m_radius;
  rec.set_face_normal(r, outward_normal);

  return true;
};

#endif
#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

double hit_sphere(const Point3& center, double radius, const Ray& r)
{
  // Compute the direction vector from the ray's origin to the center of the sphere
  Vec3 ray_to_center = r.origin() - center;

  // Compute the coefficients of the quadratic equation
  auto a = r.direction().length_squared(); // squared length of the ray direction
  auto half_b = dot(ray_to_center, r.direction()); // half of the dot product of ray_to_center and the ray direction
  auto c = ray_to_center.length_squared() - radius * radius; // squared length of ray_to_center minus the squared radius

  // Compute the discriminant
  auto discriminant = half_b * half_b - a * c;

  if (discriminant < 0)
  {
    return -1.0; // No intersection, discriminant is negative
  }
  else
  {
    auto sqrt_discriminant = sqrt(discriminant);

    // Compute the roots of the quadratic equation, e.g. t
    auto root = (-half_b - sqrt_discriminant) / a;

    if (root > 0)
    {
      return root; // Return the smaller positive root
    }
    else
    {
      return (-half_b + sqrt_discriminant) / a; // Return the larger root
    }
  }
}

Color ray_color(const Ray& r)
{
  // Check for intersection with sphere
  double closest_intersection_point = hit_sphere(Point3(0,0,-1), 0.5, r);

  // If ray intersects
  if (closest_intersection_point > 0.0)
  {
    // Calculate surface normal at intersection point
    Vec3 surface_normal = unit_vector(r.at(closest_intersection_point) - Vec3(0,0,-1));

    // Map the components of the surface normal to the color range [0, 1]
    // Unit vector so already between [-1, 1], +1 to bind values between [0, 2]
    // then multiply by 0.5 to bind between [0, 1]
    return 0.5 * Color(surface_normal.x() + 1, surface_normal.y() + 1, surface_normal.z() + 1);
  }

  // Apply a background gradient if no intersection occurs
  Vec3 unit_direction = unit_vector(r.direction());
  double t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


int main() {

    // Image

    constexpr double aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

     // Camera

     double viewport_height = 2.0;
     double viewport_width = aspect_ratio * viewport_height;
     double focal_length = 1.0;

     auto origin = Point3(0, 0, 0);
     auto horizontal = Vec3(viewport_width, 0, 0);
     auto vertical = Vec3(0, viewport_height, 0);
     auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
          double x_normalized = static_cast<double>(i) / (image_width - 1);
          double y_normalized = static_cast<double>(j) / (image_height - 1);
          Ray r(origin, lower_left_corner + x_normalized * horizontal + y_normalized * vertical - origin);
          Color pixel_color = ray_color(r);

          write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}
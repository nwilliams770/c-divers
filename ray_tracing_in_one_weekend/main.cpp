#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

double hit_sphere(const point3& sphere_center, double sphere_radius, const ray& r)
{
  // Calculate the offset vector between the ray's origin and the sphere's center
  vec3 ray_to_center = r.origin() - sphere_center;

  // Calculate the coefficients
  auto a = dot(r.direction(), r.direction());  // Coefficient of t^2
  auto b = 2.0 * dot(ray_to_center, r.direction());  // Coefficient of t
  auto c = dot(ray_to_center, ray_to_center) - sphere_radius * sphere_radius;  // Coefficient without t

  // Calculate the discriminant
  auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
      return -1.0;
    } else {
      // Solve for t, opt for operator- instead of operator+ so that we get
      // the intersection point that is closest to the origin of the ray
      return (-b - sqrt(discriminant) ) / (2.0*a);
    }

}

color ray_color(const ray& r)
{
  // Check for intersection with sphere
  double closest_intersection_point = hit_sphere(point3(0,0,-1), 0.5, r);

  // If ray intersects
  if (closest_intersection_point > 0.0)
  {
    // Calculate surface normal at intersection point
    vec3 surface_normal = unit_vector(r.at(closest_intersection_point) - vec3(0,0,-1));

    // Map the components of the surface normal to the color range [0, 1]
    // Unit vector so already between [-1, 1], +1 to bind values between [0, 2]
    // then multiply by 0.5 to bind between [0, 1]
    return 0.5 * color(surface_normal.x() + 1, surface_normal.y() + 1, surface_normal.z() + 1);
  }

  // Apply a background gradient if no intersection occurs
  vec3 unit_direction = unit_vector(r.direction());
  double t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
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

     auto origin = point3(0, 0, 0);
     auto horizontal = vec3(viewport_width, 0, 0);
     auto vertical = vec3(0, viewport_height, 0);
     auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
          double x_normalized = static_cast<double>(i) / (image_width - 1);
          double y_normalized = static_cast<double>(j) / (image_height - 1);
          ray r(origin, lower_left_corner + x_normalized * horizontal + y_normalized * vertical - origin);
          color pixel_color = ray_color(r);

          write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}
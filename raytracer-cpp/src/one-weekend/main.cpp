#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

// C = center of sphere
// P = point along the ray, solving P(t) means potential point along the ray
// Q = ray origin
// (C - P(t)) * (C-P(t)) = rˆ2
// P(t) = Q + d*t => shooting ray along its direction, solving for t
//
//(C - (Q + td))^2 = r^2
//(-td + (C - Q))^2 = r^2
//binomial formula: t^2d^2 - 2td * (C-Q) + (C-Q) * (C-Q) = r^2
//refer to a, b,c
//quadratic formula: (-b +- sqrt(b^2 - 4ac)) / 2a
//to check if we have solutions, only sqrt is interesting, we do not want the values!
//just check if there are solutions!
bool hit_sphere(const point3 &center, float radius, const ray &r) {
  vec3 oc = center - r.origin();              // (C - Q)
  auto a = dot(r.direction(), r.direction()); // d * d
  auto b = -2.0 * dot(r.direction(), oc);     // -2d * (C - Q)
  auto c = dot(oc, oc) - radius * radius;     // (C - Q) * (C - Q) * r^2

  // if square root is positive, we have 2 solutions (ray penetrates and exits sphere)
  // if square root is 0 we have 1 solution (ray hits sphere once at the edge)
  // if square root is negative, we have no solution!
  // only check for discriminant:
  auto discriminant = b * b - 4 * a * c;
  return (discriminant >= 0);
}

color ray_color(const ray &r) {
  if (hit_sphere(point3(0, 0, -1), 0.5, r))
    return color(1, 0, 0);

  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
  // image
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  // calculate image image, ensure > 1
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // camera
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width) / image_height);
  auto camera_center = point3(0, 0, 0);

  // calculate the vectors across the horizontal and down the vertical viewport
  // edges
  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  // calculate the horizontal and vertical delta vectors from pixel to pixel
  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  // calculate the location of the upper left pixel
  auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // rendering
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto pixel_center =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      auto pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone.                                    \n";
}

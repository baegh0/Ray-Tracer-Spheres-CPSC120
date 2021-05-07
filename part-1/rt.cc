// Yasmine Lee
// CPSC 120-02
// 2021-05-06
// yasmine198@csu.fullerton.edu
// @yasmine198
//
// Lab 12-01
//
// The program creates a ray tracer and outputs many spheres with more samples.
//

#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>

#include "image.h"
#include "ray.h"
#include "sphere.h"
#include "utility.h"
#include "vec3.h"

using namespace std;

Color RayColor(const Ray &r, const std::vector<std::shared_ptr<Hittable>> &world) {
  HitRecord rec;
  Color c;
  HitRecord tmp_rec;
  bool hit_anything = false;
  double t_min = 0.0;
  double closest_so_far = kInfinity;
  for (const auto &object : world) {
    if (object->hit(r, t_min, closest_so_far, tmp_rec)) {
      hit_anything = true;
      closest_so_far = tmp_rec.t;
      rec = tmp_rec;
    }
  }
  if (hit_anything) {
    c = rec.material->reflect_color(r, rec);
  } else {
    Color sky_top{0.4980392156862745, 0.7450980392156863, 0.9215686274509803};
    Color sky_bottom{1, 1, 1};
    Vec3 unit_direction = UnitVector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    c = (1.0 - t) * sky_bottom + t * sky_top;
  }
  return c;
}
void ErrorMessage(const string &message) {
  cout << message << "\n";
  cout << "There was an error. Exiting.\n";
}
int main(int argc, char const *argv[]) {
  if (argc < 2) {
    ErrorMessage("Please provide a path to a file.");
    exit(1);
  }
  string argv_one_output_file_name = string(argv[1]);
  const double kAspectRatio = 16.0 / 9.0;
  const int kImageWidth = 800;
  const int kImageHeight = int(lround(kImageWidth / kAspectRatio));
  const int kSamplesPerPixel = 50;
  Image image(argv_one_output_file_name, kImageWidth, kImageHeight);
  if (!image.is_open()) {
    ostringstream message_buffer("Could not open the file ", ios_base::ate);
    message_buffer << argv_one_output_file_name << "!";
    ErrorMessage(message_buffer.str());
    exit(1);
  }
  cout << "Image: " << image.height() << "x" << image.width() << "\n";
  const int kNumSpheres = 100;
  auto world = RandomScene(kNumSpheres);
  const double kViewportHeight = 2.0;
  const double kViewportWidth = kAspectRatio * kViewportHeight;
  const double kFocalLength = 1.0;
  const Point3 kOrigin{0, 0, 0};
  const Vec3 kHorizontal{kViewportWidth, 0, 0};
  const Vec3 kVertical{0, kViewportHeight, 0};
  const Vec3 kLowerLeftCorner =
      kOrigin - kHorizontal / 2 - kVertical / 2 - Vec3(0, 0, kFocalLength);
  chrono::time_point<chrono::high_resolution_clock> start =
      chrono::high_resolution_clock::now();
  Color pixel_color;
  for (int row = image.height() - 1; row >= 0; row--) {
    for (int column = 0; column < image.width(); column++) {
      for (int s = 0; s < kSamplesPerPixel; s++) {
        double u = (double(column) + RandomDouble01()) / double(image.width() - 1);
        double v = (double(row) + RandomDouble01()) / double(image.height() - 1);
        Ray r{kOrigin,
              kLowerLeftCorner + u * kHorizontal + v * kVertical - kOrigin};
        pixel_color = pixel_color + RayColor(r, world);
      }
      double scale = 1.0 / double(kSamplesPerPixel);
      double r = Clamp(std::sqrt(pixel_color.r() * scale), 0.0, 1.0);
      double g = Clamp(std::sqrt(pixel_color.g() * scale), 0.0, 1.0);
      double b = Clamp(std::sqrt(pixel_color.b() * scale), 0.0, 1.0);
      pixel_color = Color(r, g, b);
      image.write(pixel_color);
    }
  }
  chrono::time_point<chrono::high_resolution_clock> end =
      chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;
  cout << "Time elapsed: " << elapsed_seconds.count() << " seconds.\n";
  return 0;
}
    
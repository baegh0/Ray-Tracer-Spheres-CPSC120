
#include "utility.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>

// See the header file for documentation.

const double kInfinity = std::numeric_limits<double>::infinity();
const double kPi = 3.14159265358979323846;

double Clamp(double x, double min, double max) {
  double rv = x;
  if (x < min) {
    rv = min;
  } else if (x > max) {
    rv = max;
  }
  return rv;
}

Vec3 Clamp(const Vec3 v, double min, double max) {
  return Vec3{Clamp(v.x(), min, max), Clamp(v.y(), min, max),
              Clamp(v.z(), min, max)};
}
double Square(double x) { return x * x; }

double DegreesToRadians(double degrees) { return degrees * kPi / 180.0; }

std::vector<std::shared_ptr<Hittable>> OriginalScene() {
  std::vector<std::shared_ptr<Hittable>> world;
  auto ac = Color{0.3, 0.3, 0.0};
  auto dc = Color{0.7, 0.7, 0.0};
  auto sc = Color{0.5, 0.5, 0.0};
  auto m = std::make_shared<PhongMaterial>(ac, dc, sc, 32.0);
  world.push_back(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, m));
  return world;
}

void FiveSpheres(std::vector<std::shared_ptr<Hittable>>& world) {
  // Plain Red
  auto red_material = std::make_shared<PhongMaterial>(
      Color{0.3, 0.0, 0.0}, Color{0.7, 0.0, 0.0}, Color{0.5, 0.0, 0.0}, 32.0,
      std::string("Plain Red"));
  // Plain Green
  auto green_material = std::make_shared<PhongMaterial>(
      Color{0.0, 0.3, 0.0}, Color{0.0, 0.7, 0.0}, Color{0.0, 0.5, 0.0}, 32.0,
      std::string("Plain Green"));
  // Plain Blue
  auto blue_material = std::make_shared<PhongMaterial>(
      Color{0.0, 0.0, 0.3}, Color{0.0, 0.0, 0.7}, Color{0.0, 0.0, 0.5}, 32.0,
      std::string("Plain Blue"));
  // Plain Yellow
  auto yellow_material = std::make_shared<PhongMaterial>(
      Color{0.3, 0.3, 0.0}, Color{0.7, 0.7, 0.0}, Color{0.5, 0.5, 0.0}, 32.0,
      std::string("Plain Yellow"));
  // Plain Purple
  auto purple_material = std::make_shared<PhongMaterial>(
      Color{0.3, 0.0, 0.3}, Color{0.7, 0.7, 0.7}, Color{0.5, 0.0, 0.5}, 32.0,
      std::string("Plain Purple"));
  world.push_back(
      std::make_shared<Sphere>(Point3(0, 0, -10), 1.0, yellow_material));
  world.push_back(
      std::make_shared<Sphere>(Point3(0, 8, -10), 1.0, red_material));
  world.push_back(
      std::make_shared<Sphere>(Point3(15, 0, -10), 1.0, green_material));
  world.push_back(
      std::make_shared<Sphere>(Point3(0, -8, -10), 1.0, blue_material));
  world.push_back(
      std::make_shared<Sphere>(Point3(-15, 0, -10), 1.0, purple_material));
}

std::vector<std::shared_ptr<Hittable>> RandomScene(int num_elements) {
  auto phong_material_array = make_phong_material_array();
  std::vector<std::shared_ptr<Hittable>> world;

  FiveSpheres(world);

  // Shuffle the colors for the random spheres
  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(phong_material_array.begin(), phong_material_array.end(), gen);

  for (int i = 0; i < num_elements; i++) {
    Vec3 sphere_center = (random_in_unit_sphere() * RandomDouble(-5, 5)) +
                         Vec3{0, 0, RandomDouble(-3, -10)};
    double sphere_radius = 0.25;
    try {
      auto sphere_material =
          phong_material_array.at(i % phong_material_array.size());
      world.push_back(std::make_shared<Sphere>(sphere_center, sphere_radius,
                                               sphere_material));
    } catch (const std::exception& e) {
      std::cout << "Exception attempting to fetch material at location " << i
                << "\n";
      std::cout << e.what() << "\n";
      exit(1);
    }
  }
  // Print out the spheres to aid in debugging
  std::cout << "--- World Definition Begin ---\n";
  for (auto s : world) {
    std::cout << *(std::dynamic_pointer_cast<Sphere>(s)) << "\n";
  }
  std::cout << "--- World Definition End ---\n";

  return world;
}

std::map<std::string, std::shared_ptr<PhongMaterial>>
make_phong_material_map() {
  std::map<std::string, std::shared_ptr<PhongMaterial>> phong_material_map{
      // Brass
      {"Brass",
       std::make_shared<PhongMaterial>(Color{0.329412, 0.223529, 0.027451},
                                       Color{0.780392, 0.568627, 0.113725},
                                       Color{0.992157, 0.941176, 0.807843},
                                       27.8974, std::string("Brass"))},
      // Bronze
      {"Bronze",
       std::make_shared<PhongMaterial>(
           Color{0.2125, 0.1275, 0.054}, Color{0.714, 0.4284, 0.18144},
           Color{0.393548, 0.271906, 0.166721}, 25.6, std::string("Bronze"))},
      // Polished Bronze
      {"Polished Bronze",
       std::make_shared<PhongMaterial>(Color{0.25, 0.148, 0.06475},
                                       Color{0.4, 0.2368, 0.1036},
                                       Color{0.774597, 0.458561, 0.200621},
                                       76.8, std::string("Polished Bronze"))},
      // Chrome
      {"Chrome",
       std::make_shared<PhongMaterial>(
           Color{0.25, 0.25, 0.25}, Color{0.4, 0.4, 0.4},
           Color{0.774597, 0.774597, 0.774597}, 76.8, std::string("Chrome"))},
      // Copper
      {"Copper",
       std::make_shared<PhongMaterial>(
           Color{0.19125, 0.0735, 0.0225}, Color{0.7038, 0.27048, 0.0828},
           Color{0.256777, 0.137622, 0.086014}, 12.8, std::string("Copper"))},
      // Polished Copper
      {"Polished Copper",
       std::make_shared<PhongMaterial>(Color{0.2295, 0.08825, 0.0275},
                                       Color{0.5508, 0.2118, 0.066},
                                       Color{0.580594, 0.223257, 0.0695701},
                                       51.2, std::string("Polished Copper"))},
      // Gold
      {"Gold",
       std::make_shared<PhongMaterial>(
           Color{0.24725, 0.1995, 0.0745}, Color{0.75164, 0.60648, 0.22648},
           Color{0.628281, 0.555802, 0.366065}, 51.2, std::string("Gold"))},
      // Polished Gold
      {"Polished Gold",
       std::make_shared<PhongMaterial>(Color{0.24725, 0.2245, 0.0645},
                                       Color{0.34615, 0.3143, 0.0903},
                                       Color{0.797357, 0.723991, 0.208006},
                                       83.2, std::string("Polished Gold"))},
      // Tin
      {"Tin",
       std::make_shared<PhongMaterial>(Color{0.105882, 0.058824, 0.113725},
                                       Color{0.427451, 0.470588, 0.541176},
                                       Color{0.333333, 0.333333, 0.521569},
                                       9.84615, std::string("Tin"))},
      // Silver
      {"Silver",
       std::make_shared<PhongMaterial>(
           Color{0.19225, 0.19225, 0.19225}, Color{0.50754, 0.50754, 0.50754},
           Color{0.508273, 0.508273, 0.508273}, 51.2, std::string("Silver"))},
      // Polished Silver
      {"Polished Silver",
       std::make_shared<PhongMaterial>(Color{0.23125, 0.23125, 0.23125},
                                       Color{0.2775, 0.2775, 0.2775},
                                       Color{0.773911, 0.773911, 0.773911},
                                       89.6, std::string("Polished Silver"))},
      // Emerald
      {"Emerald",
       std::make_shared<PhongMaterial>(
           Color{0.039090909090909086, 0.3172727272727272,
                 0.039090909090909086},
           Color{0.13759999999999997, 1.1168, 0.13759999999999997},
           Color{1.1509090909090909, 1.323292727272727, 1.1509090909090909},
           76.8, std::string("Emerald"))},
      // Jade
      {"Jade",
       std::make_shared<PhongMaterial>(
           Color{0.14210526315789476, 0.23421052631578948, 0.16578947368421054},
           Color{0.568421052631579, 0.9368421052631579, 0.6631578947368422},
           Color{0.33287157894736846, 0.33287157894736846, 0.33287157894736846},
           12.8, std::string("Jade"))},
      // Obsidian
      {"Obsidian",
       std::make_shared<PhongMaterial>(
           Color{0.06554878048780488, 0.06097560975609757, 0.08079268292682927},
           Color{0.2228658536585366, 0.20731707317073172, 0.27469512195121953},
           Color{0.4057817073170732, 0.4007731707317073, 0.4224817073170732},
           38.4, std::string("Obsidian"))},
      // Perl
      {"Perl",
       std::make_shared<PhongMaterial>(
           Color{0.27114967462039047, 0.22478308026030366, 0.22478308026030366},
           Color{1.0845986984815619, 0.8991323210412147, 0.8991323210412147},
           Color{0.32174403470715834, 0.32174403470715834, 0.32174403470715834},
           11.264, std::string("Perl"))},
      // Ruby
      {"Ruby",
       std::make_shared<PhongMaterial>(
           Color{0.3172727272727272, 0.021363636363636362,
                 0.021363636363636362},
           Color{1.1168, 0.07519999999999999, 0.07519999999999999},
           Color{1.323292727272727, 1.1399254545454545, 1.1399254545454545},
           76.8, std::string("Ruby"))},
      // Turquoise
      {"Turquoise", std::make_shared<PhongMaterial>(
                        Color{0.125, 0.23406249999999998, 0.21812499999999999},
                        Color{0.495, 0.9268875, 0.863775},
                        Color{0.3715675, 0.3853625, 0.3833475}, 12.8,
                        std::string("Turquoise"))},
      // Black Plastic
      {"Black Plastic",
       std::make_shared<PhongMaterial>(
           Color{0.0, 0.0, 0.0}, Color{0.01, 0.01, 0.01}, Color{0.5, 0.5, 0.5},
           32.0, std::string("Black Plastic"))},
      // Cyan Plastic
      {"Cyan Plastic",
       std::make_shared<PhongMaterial>(
           Color{0.0, 0.1, 0.06}, Color{0.0, 0.50980392, 0.50980392},
           Color{0.50196078, 0.50196078, 0.50196078}, 32.0,
           std::string("Cyan Plastic"))},
      // Green Plastic
      {"Green Plastic",
       std::make_shared<PhongMaterial>(
           Color{0.0, 0.0, 0.0}, Color{0.1, 0.35, 0.1}, Color{0.45, 0.55, 0.45},
           32.0, std::string("Green Plastic"))},
      // Red Plastic
      {"Red Plastic",
       std::make_shared<PhongMaterial>(
           Color{0.0, 0.0, 0.0}, Color{0.5, 0.0, 0.0}, Color{0.7, 0.6, 0.6},
           32.0, std::string("Red Plastic"))},
      // White Plastic
      {"White Plastic",
       std::make_shared<PhongMaterial>(
           Color{0.0, 0.0, 0.0}, Color{0.55, 0.55, 0.55}, Color{0.7, 0.7, 0.7},
           32.0, std::string("White Plastic"))},
      // Yellow Plastic
      {"Yellow Plastic",
       std::make_shared<PhongMaterial>(
           Color{0.0, 0.0, 0.0}, Color{0.5, 0.5, 0.0}, Color{0.6, 0.6, 0.5},
           32.0, std::string("Yellow Plastic"))},
      // Black Rubber
      {"Black Rubber",
       std::make_shared<PhongMaterial>(
           Color{0.02, 0.02, 0.02}, Color{0.01, 0.01, 0.01},
           Color{0.4, 0.4, 0.4}, 10.0, std::string("Black Rubber"))},
      // Cyan Rubber
      {"Cyan Rubber",
       std::make_shared<PhongMaterial>(
           Color{0.0, 0.05, 0.05}, Color{0.4, 0.5, 0.5}, Color{0.04, 0.7, 0.7},
           10.0, std::string("Cyan Rubber"))},
      // Green Rubber
      {"Green Rubber",
       std::make_shared<PhongMaterial>(
           Color{0.0, 0.05, 0.0}, Color{0.4, 0.5, 0.4}, Color{0.04, 0.7, 0.04},
           10.0, std::string("Green Rubber"))},
      // Red Rubber
      {"Red Rubber",
       std::make_shared<PhongMaterial>(
           Color{0.05, 0.0, 0.0}, Color{0.5, 0.4, 0.4}, Color{0.7, 0.04, 0.04},
           10.0, std::string("Red Rubber"))},
      // White Rubber
      {"White Rubber",
       std::make_shared<PhongMaterial>(
           Color{0.05, 0.05, 0.05}, Color{0.5, 0.5, 0.5}, Color{0.7, 0.7, 0.7},
           10.0, std::string("White Rubber"))},
      // Yellow Rubber
      {"Yellow Rubber",
       std::make_shared<PhongMaterial>(
           Color{0.05, 0.05, 0.0}, Color{0.5, 0.5, 0.4}, Color{0.7, 0.7, 0.04},
           10.0, std::string("Yellow Rubber"))},
  };
  return phong_material_map;
}

std::array<std::shared_ptr<PhongMaterial>, 29> make_phong_material_array() {
  std::array<std::shared_ptr<PhongMaterial>, 29> phong_material_array{
      // Brass
      std::make_shared<PhongMaterial>(Color{0.329412, 0.223529, 0.027451},
                                      Color{0.780392, 0.568627, 0.113725},
                                      Color{0.992157, 0.941176, 0.807843},
                                      27.8974, std::string("Brass")),
      // Bronze
      std::make_shared<PhongMaterial>(
          Color{0.2125, 0.1275, 0.054}, Color{0.714, 0.4284, 0.18144},
          Color{0.393548, 0.271906, 0.166721}, 25.6, std::string("Bronze")),
      // Polished Bronze
      std::make_shared<PhongMaterial>(Color{0.25, 0.148, 0.06475},
                                      Color{0.4, 0.2368, 0.1036},
                                      Color{0.774597, 0.458561, 0.200621}, 76.8,
                                      std::string("Polished Bronze")),
      // Chrome
      std::make_shared<PhongMaterial>(
          Color{0.25, 0.25, 0.25}, Color{0.4, 0.4, 0.4},
          Color{0.774597, 0.774597, 0.774597}, 76.8, std::string("Chrome")),
      // Copper
      std::make_shared<PhongMaterial>(
          Color{0.19125, 0.0735, 0.0225}, Color{0.7038, 0.27048, 0.0828},
          Color{0.256777, 0.137622, 0.086014}, 12.8, std::string("Copper")),
      // Polished Copper
      std::make_shared<PhongMaterial>(Color{0.2295, 0.08825, 0.0275},
                                      Color{0.5508, 0.2118, 0.066},
                                      Color{0.580594, 0.223257, 0.0695701},
                                      51.2, std::string("Polished Copper")),
      // Gold
      std::make_shared<PhongMaterial>(
          Color{0.24725, 0.1995, 0.0745}, Color{0.75164, 0.60648, 0.22648},
          Color{0.628281, 0.555802, 0.366065}, 51.2, std::string("Gold")),
      // Polished Gold
      std::make_shared<PhongMaterial>(Color{0.24725, 0.2245, 0.0645},
                                      Color{0.34615, 0.3143, 0.0903},
                                      Color{0.797357, 0.723991, 0.208006}, 83.2,
                                      std::string("Polished Gold")),
      // Tin
      std::make_shared<PhongMaterial>(Color{0.105882, 0.058824, 0.113725},
                                      Color{0.427451, 0.470588, 0.541176},
                                      Color{0.333333, 0.333333, 0.521569},
                                      9.84615, std::string("Tin")),
      // Silver
      std::make_shared<PhongMaterial>(
          Color{0.19225, 0.19225, 0.19225}, Color{0.50754, 0.50754, 0.50754},
          Color{0.508273, 0.508273, 0.508273}, 51.2, std::string("Silver")),
      // Polished Silver
      std::make_shared<PhongMaterial>(Color{0.23125, 0.23125, 0.23125},
                                      Color{0.2775, 0.2775, 0.2775},
                                      Color{0.773911, 0.773911, 0.773911}, 89.6,
                                      std::string("Polished Silver")),
      // Emerald
      std::make_shared<PhongMaterial>(
          Color{0.039090909090909086, 0.3172727272727272, 0.039090909090909086},
          Color{0.13759999999999997, 1.1168, 0.13759999999999997},
          Color{1.1509090909090909, 1.323292727272727, 1.1509090909090909},
          76.8, std::string("Emerald")),
      // Jade
      std::make_shared<PhongMaterial>(
          Color{0.14210526315789476, 0.23421052631578948, 0.16578947368421054},
          Color{0.568421052631579, 0.9368421052631579, 0.6631578947368422},
          Color{0.33287157894736846, 0.33287157894736846, 0.33287157894736846},
          12.8, std::string("Jade")),
      // Obsidian
      std::make_shared<PhongMaterial>(
          Color{0.06554878048780488, 0.06097560975609757, 0.08079268292682927},
          Color{0.2228658536585366, 0.20731707317073172, 0.27469512195121953},
          Color{0.4057817073170732, 0.4007731707317073, 0.4224817073170732},
          38.4, std::string("Obsidian")),
      // Perl
      std::make_shared<PhongMaterial>(
          Color{0.27114967462039047, 0.22478308026030366, 0.22478308026030366},
          Color{1.0845986984815619, 0.8991323210412147, 0.8991323210412147},
          Color{0.32174403470715834, 0.32174403470715834, 0.32174403470715834},
          11.264, std::string("Perl")),
      // Ruby
      std::make_shared<PhongMaterial>(
          Color{0.3172727272727272, 0.021363636363636362, 0.021363636363636362},
          Color{1.1168, 0.07519999999999999, 0.07519999999999999},
          Color{1.323292727272727, 1.1399254545454545, 1.1399254545454545},
          76.8, std::string("Ruby")),
      // Turquoise
      std::make_shared<PhongMaterial>(
          Color{0.125, 0.23406249999999998, 0.21812499999999999},
          Color{0.495, 0.9268875, 0.863775},
          Color{0.3715675, 0.3853625, 0.3833475}, 12.8,
          std::string("Turquoise")),
      // Black Plastic
      std::make_shared<PhongMaterial>(
          Color{0.0, 0.0, 0.0}, Color{0.01, 0.01, 0.01}, Color{0.5, 0.5, 0.5},
          32.0, std::string("Black Plastic")),
      // Cyan Plastic
      std::make_shared<PhongMaterial>(Color{0.0, 0.1, 0.06},
                                      Color{0.0, 0.50980392, 0.50980392},
                                      Color{0.50196078, 0.50196078, 0.50196078},
                                      32.0, std::string("Cyan Plastic")),
      // Green Plastic
      std::make_shared<PhongMaterial>(
          Color{0.0, 0.0, 0.0}, Color{0.1, 0.35, 0.1}, Color{0.45, 0.55, 0.45},
          32.0, std::string("Green Plastic")),
      // Red Plastic
      std::make_shared<PhongMaterial>(
          Color{0.0, 0.0, 0.0}, Color{0.5, 0.0, 0.0}, Color{0.7, 0.6, 0.6},
          32.0, std::string("Red Plastic")),
      // White Plastic
      std::make_shared<PhongMaterial>(
          Color{0.0, 0.0, 0.0}, Color{0.55, 0.55, 0.55}, Color{0.7, 0.7, 0.7},
          32.0, std::string("White Plastic")),
      // Yellow Plastic
      std::make_shared<PhongMaterial>(
          Color{0.0, 0.0, 0.0}, Color{0.5, 0.5, 0.0}, Color{0.6, 0.6, 0.5},
          32.0, std::string("Yellow Plastic")),
      // Black Rubber
      std::make_shared<PhongMaterial>(
          Color{0.02, 0.02, 0.02}, Color{0.01, 0.01, 0.01},
          Color{0.4, 0.4, 0.4}, 10.0, std::string("Black Rubber")),
      // Cyan Rubber
      std::make_shared<PhongMaterial>(
          Color{0.0, 0.05, 0.05}, Color{0.4, 0.5, 0.5}, Color{0.04, 0.7, 0.7},
          10.0, std::string("Cyan Rubber")),
      // Green Rubber
      std::make_shared<PhongMaterial>(
          Color{0.0, 0.05, 0.0}, Color{0.4, 0.5, 0.4}, Color{0.04, 0.7, 0.04},
          10.0, std::string("Green Rubber")),
      // Red Rubber
      std::make_shared<PhongMaterial>(
          Color{0.05, 0.0, 0.0}, Color{0.5, 0.4, 0.4}, Color{0.7, 0.04, 0.04},
          10.0, std::string("Red Rubber")),
      // White Rubber
      std::make_shared<PhongMaterial>(
          Color{0.05, 0.05, 0.05}, Color{0.5, 0.5, 0.5}, Color{0.7, 0.7, 0.7},
          10.0, std::string("White Rubber")),
      // Yellow Rubber
      std::make_shared<PhongMaterial>(
          Color{0.05, 0.05, 0.0}, Color{0.5, 0.5, 0.4}, Color{0.7, 0.7, 0.04},
          10.0, std::string("Yellow Rubber")),
  };

  return phong_material_array;
}

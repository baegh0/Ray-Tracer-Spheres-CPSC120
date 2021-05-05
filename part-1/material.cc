#include "material.h"

#include <array>
#include <map>

#include "utility.h"

// See the header file for documentation.

Color PhongMaterial::reflect_color(const Ray& r, const HitRecord& rec) const {
  Vec3 light_position{20, 20, -1};
  Color light_color{1, 1, 1};

  Vec3 to_light_vector = UnitVector(light_position - rec.p);
  Vec3 unit_normal = UnitVector(rec.normal);
  Vec3 to_viewer = UnitVector(-rec.p);
  Vec3 reflection = Reflect(to_light_vector, unit_normal);

  Color phong_ambient = ambient_ * light_color;

  double l_dot_n = std::max(Dot(to_light_vector, unit_normal), 0.0);
  Color phong_diffuse = diffuse_ * l_dot_n * light_color;

  double r_dot_v = std::max(Dot(reflection, to_viewer), 0.0);
  double r_dot_v_to_alpha = std::pow(r_dot_v, shininess_);
  Color phong_specular = specular_ * r_dot_v_to_alpha * light_color;

  Color phong = phong_ambient + phong_diffuse + phong_specular;
  phong = Clamp(phong, 0, 1);

  return phong;
}

std::string PhongMaterial::name() { return name_; }

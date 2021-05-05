
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "hittable.h"
#include "ray.h"
#include "vec3.h"

/// An abstract base class that defines the material our objects are
/// made out of.
/// While we are experimenting with the
/// [Phong Reflection Model]
/// (https://en.wikipedia.org/wiki/Phong_reflection_model)
/// we will keep the reflect_color() method in this base class defintion.
/// When you wish to venture further, remove reflect_color and replace it
/// with the appropriate virtual methods for the abstract base class
/// representing your materials.
class Material {
 public:
  Material() = default;
  Material(const Material& m) = default;
  Material& operator=(const Material& m) = default;
  Material(Material&& m) = default;
  Material& operator=(Material&& h) = default;
  virtual ~Material() = default;

  /// The color reflected by the surface at the point given by rec and the
  /// Ray r which intersected the object. Use the material pointer in rec
  /// to calculate the reflected color.
  virtual Color reflect_color(const Ray& r, const HitRecord& rec) const = 0;
};

/// PhongMaterial is a concrete class which represents a material that
/// reflects light according to the [Phong Reflection Model]
/// (https://en.wikipedia.org/wiki/Phong_reflection_model).
/// The data members store the ambient, diffuse, and specular reflection
/// colors and the object's shininess. To aide debugging, each material
/// instance can be given a name.
class PhongMaterial : public Material {
 private:
  Color ambient_;
  Color diffuse_;
  Color specular_;
  double shininess_;
  std::string name_;

 public:
  PhongMaterial(const Color& ambient, const Color& diffuse,
                const Color& specular, double shininess,
                std::string name = std::string{"No Name"})
      : ambient_{ambient},
        diffuse_{diffuse},
        specular_{specular},
        shininess_{shininess},
        name_{name} {};
  /// The color that is reflected back at the point stored in rec
  /// calculated using the Phong Reflection model.
  Color reflect_color(const Ray& r, const HitRecord& rec) const override;
  /// Return the name of the material. By default, a material is given
  /// the name "No Name" unless a name is provided when the material is
  /// created.
  std::string name();
};

#endif
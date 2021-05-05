
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <cmath>
#include <iostream>
#include <memory>

#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

/// A sphere is defined by a center and a radius. It is a `hittable` object
/// so it implements the hittable interface and can be intersected with
/// a ray.
class Sphere : public Hittable {
 private:
  /// The center of the sphere
  Point3 center_;
  /// The radius of the sphere
  double radius_;
  /// The material properties of the sphere
  std::shared_ptr<Material> material_;

 public:
  /// Construct a sphere given a point in space and a radius
  /// \param center The center of the sphere
  /// \param radius The radius of the pshere
  /// \param material A pointer to material properties
  Sphere(Point3 center, double radius, std::shared_ptr<Material> material)
      : center_(center), radius_(radius), material_{material} {};
  /// Construct a sphere given a point in space and a radius
  /// \param center The center of the sphere
  /// \param radius The radius of the pshere
  Sphere(Point3 center, double radius)
      : center_(center), radius_(radius), material_{nullptr} {};

  ~Sphere() override = default;

  Sphere& operator=(Sphere&& s) = default;
  Sphere(Sphere&& s) = default;
  Sphere(const Sphere& s) = default;
  Sphere& operator=(const Sphere& s) = default;

  // Remove unwanted constructors, copy, and move operations.
  Sphere() = delete;

  /// Return the center of the sphere
  Point3 center() const;
  /// Return the radius of the sphere
  double radius() const;
  /// Return the sphere's material pointer
  std::shared_ptr<Material> material() const;

  /// Override the hittable hit() method with one that is correct for spheres.
  /// The ray \p r is tested over the interval \p t_min to \p t_max for
  /// intersection with the sphere. If there is an intersection return
  /// true and update the HitRecord \p rec with the data needed for shading.
  /// \param r The ray to check for intersection against
  /// \param t_min The minnimum value of the interval to test the ray for
  /// instersection
  /// \param t_max The maximum value of the interval to test the ray for
  /// intersection
  /// \param rec The HitRecord to store the data needed for shading
  /// \remarks This overrides the method defined in the Hittable class.
  bool hit(const Ray& r, double t_min, double t_max,
           HitRecord& rec) const override;
};

/// Output a sphere to an ostream
/// \param out An output stream such as cout
/// \param s A sphere
/// \returns An output stream (it returns out)
std::ostream& operator<<(std::ostream& out, const Sphere& s);

#endif

#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include <memory>

#include "ray.h"

// Forward declaration of the Material class needed for the HitRecord
class Material;

/// HitRecord for data assciated with ray-object intersection
/// A struct is like a class yet it is typically used to store
/// Plain Old Data (POD). When a ray strikes a hittable object,
/// the hit is recorded in an instance of this struct.
/// [POD or Passive Data Structure]
/// (https://en.wikipedia.org/wiki/Passive_data_structure)
struct HitRecord {
  /// The point where a ray has struck the object
  Point3 p;
  /// The [normal](https://en.wikipedia.org/wiki/Normal_(geometry)) to the
  /// point where the ray struck the object
  Vec3 normal;
  /// A pointer to the hit's material property; given by the object struck
  std::shared_ptr<Material> material;
  /// If the ray is evaluated at t, the point p is yieled. Recall that
  /// a point P(t) can be found on a ray by evaluating the ray at t
  /// O + td, where O is the ray origin and d is the vector direction.
  double t = NAN;
};

/// An abstract class defining what it means to be hittable by a ray.
/// This class is never instantiated. Instead it is used to inherit the
/// trait of being hittable. All hittable objects must implement the
/// methods bool hit() so what if a ray is given a hit can be found
/// between t_min and t_max. The hit is stored in rec.
/// This class has a [default constructor]
/// (https://en.cppreference.com/w/cpp/language/default_constructor),
/// a default copy constructor, a default destructor, and a default
/// copy assignment operator. The move constructor, and move assignment
/// operator are deleted from the class.
class Hittable {
 public:
  Hittable() = default;

  /// Hittable does not have a [move assignment operator]
  /// (https://en.cppreference.com/w/cpp/language/move_assignment).
  Hittable(const Hittable& h) = default;
  Hittable& operator=(const Hittable& h) = default;

  /// The hittable class has a default [move constructor]
  /// (https://en.cppreference.com/w/cpp/language/move_constructor).
  Hittable(Hittable&& h) = default;
  Hittable& operator=(Hittable&& h) = default;

  virtual ~Hittable() = default;

  /// Virtual method hit must be defined by any class that inherits from
  /// this class. In essence, if a class inherits from hittable, then
  /// this method means that you can check to see if a ray intersects
  /// with the object.
  virtual bool hit(const Ray& r, double t_min, double t_max,
                   HitRecord& rec) const = 0;
};

#endif
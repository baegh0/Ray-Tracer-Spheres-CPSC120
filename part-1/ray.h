
#ifndef _RAY_H_
#define _RAY_H_

#include <iostream>

#include "vec3.h"

/// The ray class represents a geometric ray which represents a point in
/// space (the origin) and a direction vector. A ray is used to calculate
/// what is visible in the image because we follow a ray through space to see
/// what it collides with (what it sees) and then use this information to
/// calculate the color. Because we have to stretch the ray through the
/// imaginary space we are visualizing, we have to be able to evaluate the
/// ray at any given value of t. This means that given some value t, we can
/// evaluate the ray and find the point in space that it points at.
/// See https://en.wikipedia.org/wiki/Line_(geometry)#Ray and
/// https://mathworld.wolfram.com/Ray.html
/// Generally, we can think of a ray as a parametric line,
/// P(t) = O + td
/// where any point can be found the line passing through the point O
/// in the direction d by evaluating the function for every value of t.

class Ray {
 private:
  /// The origin of the ray, a point in 3D space
  Point3 origin_;
  /// The direction that we will move in from the ray's origin
  Vec3 direction_;

 public:
  /// The constructor creates a ray given an 3D point as the \p origin and
  /// a 3D vector as the \p direction from the point.
  /// \param origin A 3D point in space
  /// \param direction A 3D vector representing the direction
  Ray(const Point3& origin, const Vec3& direction)
      : origin_(origin), direction_(direction){};

  /// Return the Ray's origin (starting point)
  /// \returns The ray's origin
  Point3 origin() const;

  /// Return the ray's direction
  /// \returns The ray's direction
  Vec3 direction() const;

  /// Evaluate the ray at \p t and return the point that the ray points to
  /// Given a double \p t, evaluate (plug in) the value into the ray equation
  /// and calculate the point that the ray points to.
  /// P(t) = O + td
  /// P(t) is the point at value t
  /// O is the origin
  /// t is the parameter \p t
  /// d is the direction
  /// \param t A positive or negative floating point value
  /// \returns A 3D point that the ray points at.
  Point3 at(double t) const;
};

/// Output a ray to an ostream
/// \param out An output stream such as cout
/// \param r A ray
/// \returns An output stream (it returns out)
std::ostream& operator<<(std::ostream& out, const Ray& r);

#endif
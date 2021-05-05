
#include "sphere.h"

#include "utility.h"

// See the header file for documentation.

Point3 Sphere::center() const { return center_; }

double Sphere::radius() const { return radius_; }

std::shared_ptr<Material> Sphere::material() const { return material_; }

bool Sphere::hit(const Ray& r, double t_min, double t_max,
                 HitRecord& rec) const {
  // Get a vector from the ray's origin to the sphere's center
  Vec3 oc = r.origin() - center_;
  // t^2 d \cdot d + 2 t d \cdot (O - C) + (O - C) \cdot (O - C) - r^2 = 0
  // where a is t^2  d \cdot d
  // b is 2 t d \cdot (O - C) + (O - C)
  // and c is (O - C) \cdot (O - C) - r^2
  double a = Dot(r.direction(), r.direction());
  double b = 2.0 * Dot(oc, r.direction());
  double c = Dot(oc, oc) - Square(radius_);
  // If the discriminant is greater than zero then the ray strikes the
  // sphere 1 or more times; else the ray does not strike the sphere
  double discriminant = Square(b) - (4 * a * c);

  // Short circuit out of the function if the discriminant is less than zero.
  // There are no real roots when discriminant is less than zero.
  if (discriminant < 0) {
    return false;
  }

  auto discriminant_sqrt = std::sqrt(discriminant);
  // return the solution that is on the closest side of the sphere
  // Apply the quadratic equation
  // x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}
  auto root = (-b - discriminant_sqrt) / (2.0 * a);
  // If our solution is outside of our ray's t_min and t_max
  if (root < t_min || t_max < root) {
    // Look at the other solution
    root = (-b + discriminant_sqrt) / (2.0 * a);
    // If our solution is outside of our ray's t_min and t_max
    if (root < t_min || t_max < root) {
      // Again short circuit out.
      return false;
    }
  }
  // Set the hit record because we know we have a valid root at this point.
  rec.t = root;
  rec.p = r.at(rec.t);
  rec.normal = (rec.p - center_) / radius_;
  rec.material = material_;
  return true;
}

std::ostream& operator<<(std::ostream& out, const Sphere& s) {
  // Fetching the name only works for Phong materials.
  auto m = std::dynamic_pointer_cast<PhongMaterial>(s.material());
  out << "Sphere(center=" << s.center() << ", radius=" << s.radius()
      << ", material=\"" << m->name() << "\")";
  return out;
}

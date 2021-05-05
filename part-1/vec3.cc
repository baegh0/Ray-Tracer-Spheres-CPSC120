
#include "vec3.h"

#include "rng.h"

// See the header file for documentation.

double Vec3::x() const { return x_; }
double Vec3::y() const { return y_; }
double Vec3::z() const { return z_; }

double Vec3::r() const { return r_; }
double Vec3::g() const { return g_; }
double Vec3::b() const { return b_; }

Vec3 Vec3::operator-() const { return Vec3{-x_, -y_, -z_}; }

double Vec3::operator[](int i) const { return data_[i]; }
double& Vec3::operator[](int i) { return data_[i]; }

double Vec3::length() const { return std::sqrt(length_squared()); }

double Vec3::length_squared() const { return x_ * x_ + y_ * y_ + z_ * z_; }

Vec3 Vec3::random_01() {
  return Vec3{RandomDouble01(), RandomDouble01(), RandomDouble01()};
}

Vec3 Vec3::random_11() {
  return Vec3{RandomDouble11(), RandomDouble11(), RandomDouble11()};
}

Vec3 Vec3::random(double min, double max) {
  return Vec3{RandomDouble(min, max), RandomDouble(min, max),
              RandomDouble(min, max)};
}

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
  out << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
  return out;
}

Vec3 operator+(const Vec3& u, const Vec3& v) {
  return (Vec3{u.x() + v.x(), u.y() + v.y(), u.z() + v.z()});
}

Vec3 operator-(const Vec3& u, const Vec3& v) {
  return (Vec3{u.x() - v.x(), u.y() - v.y(), u.z() - v.z()});
}

Vec3 operator*(double t, const Vec3& v) {
  return Vec3{t * v.x(), t * v.y(), t * v.z()};
}

Vec3 operator*(const Vec3& v, double t) { return t * v; }

Vec3 operator*(const Vec3& u, const Vec3& v) {
  return Vec3{u.x() * v.x(), u.y() * v.y(), u.z() * v.z()};
}

Vec3 operator/(const Vec3& v, double t) { return (1.0 / t) * v; }

double Dot(const Vec3& u, const Vec3& v) {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

Vec3 Cross(const Vec3& u, const Vec3& v) {
  return Vec3{u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x()};
}

Vec3 UnitVector(const Vec3& v) { return v / v.length(); }

Vec3 Reflect(const Vec3& v, const Vec3& n) { return (2 * Dot(v, n) * n) - v; }

Vec3 random_in_unit_sphere() {
  double theta = 2 * M_PI * RandomDouble01();
  double phi = acos(1 - 2 * RandomDouble01());
  double x = sin(phi) * cos(theta);
  double y = sin(phi) * sin(theta);
  double z = cos(phi);
  return Vec3{x, y, z};
}

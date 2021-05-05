
#ifndef _VEC3_H_
#define _VEC3_H_

#include <cmath>
#include <iostream>

#include "rng.h"

/// A 3 dimensional vector class to represent vectors, points, and colors
class Vec3 {
 private:
  // This is a fancy trick (from the days of C) to say that we have
  // three doubles named x_, y_, and z_ and we can also refer to the
  // very same variables as r_, g_, and b_, and as the C array data_.
  // Be careful with this little trick.
  // We should all really use C++ 17's std::variant
  // https://en.cppreference.com/w/cpp/utility/variant
  union {
    struct {
      double x_, y_, z_;
    };
    struct {
      double r_, g_, b_;
    };
    struct {
      double data_[3];
    };
  };

 public:
  /// The default constructor for Vec3 creates a Vec3 initialized
  /// to a zero vector.
  Vec3() : x_{0.0}, y_{0.0}, z_{0.0} {};

  /// Constructor to initialize a Vec3 with \p x, \p y, and \p z.
  Vec3(double x, double y, double z) : x_{x}, y_{y}, z_{z} {};

  /// Return the value of x
  /// \returns the value of x_
  double x() const;

  /// Return the value of y
  /// \returns the value of y_
  double y() const;

  /// Return the value of z
  /// \returns the value of z_
  double z() const;

  /// Return the value of r
  /// \returns the value of r_
  double r() const;

  /// Return the value of g
  /// \returns the value of g_
  double g() const;

  /// Return the value of b
  /// \returns the value of b_
  double b() const;

  /// Negation operator
  /// \returns a copy of *this negated.
  Vec3 operator-() const;

  /// Operator [] which allows the object to be treated like a
  /// a C array. This is a const version so it can only be used for reading.
  /// Vec3 foo{1, 2, 3};
  /// double val = foo[1];
  double operator[](int i) const;
  /// Operator [] which allows the object to be treated like a
  /// a C array. This is a non-const version which returns a reference
  /// so it can be used for writing.
  /// Vec3 foo{1, 2, 3};
  /// foo[1] = 42;
  double& operator[](int i);

  /// Calculate the length of a vector using the distance formula.
  /// d = sqrt(x*x + y*y + z*z)
  /// \returns the length of the vector
  double length() const;

  /// Calculate the squared length of a vector using the distance formula.
  /// This is fast and useful when one wants to compare relative distances
  /// or when you wish to determine if a vector is of unit length.
  /// d = x*x + y*y + z*z
  /// \returns the squared length of the vector
  double length_squared() const;

  /// Return a Vec3 with each component set to a random value between 0 and 1
  static Vec3 random_01();

  /// Return a Vec3 with each component set to a random value between -1 and 1
  static Vec3 random_11();

  /// Return a Vec3 with each component set to a random value
  /// between \p min and \p max
  static Vec3 random(double min, double max);
};

/// Sum \p u and \p v together
/// \param u The left hand operand of the operator
/// \param v The right hand operand of the operator
/// \returns The sum of \p u and \p v as a new Vec3.
Vec3 operator+(const Vec3& u, const Vec3& v);

/// Difference of \p u and \p v together
/// \param u The left hand operand of the operator
/// \param v The right hand operand of the operator
/// \returns The difference of \p u and \p v as a new Vec3.
Vec3 operator-(const Vec3& u, const Vec3& v);

/// Product of \p t and \p v
/// Where \p t is a scalar value and \p v is a Vec3, scale \p v with \p t.
/// \param t The left hand operand of the operator
/// \param v The right hand operand of the operator
/// \returns The product of \p t and \p v as a new Vec3.
Vec3 operator*(double t, const Vec3& v);

/// Product of \p v and \p t
/// Where \p t is a scalar value and \p v is a Vec3, scale \p v with \p t.
/// \param v The left hand operand of the operator
/// \param t The right hand operand of the operator
/// \returns The product of \p t and \p v as a new Vec3.
Vec3 operator*(const Vec3& v, double t);

/// Product of \p u and \p v - this operation is for Color not Vectors!
/// Multiply the components of \p u with the components of \p v and
/// return the product
/// \param u The left hand operand of the opertor
/// \param v The right hand operand of the operator
/// \returns The product of \p u and \p v as a Vec3
/// \remark This is not used for Vectors!
Vec3 operator*(const Vec3& u, const Vec3& v);

/// Quotient of \p v and \p t
/// Where \p t is a scalar value and \p v is a Vec3, scale \p v with 1/t.
/// \param v The left hand operand of the operator
/// \param t The right hand operand of the operator
/// \returns The product of \p t and \p v as a new Vec3.
Vec3 operator/(const Vec3& v, double t);

/// The dot product of two Vec3 objects.
/// The [dot product](https://en.wikipedia.org/wiki/Dot_product) is
/// the cosine of the angle formed between the two Vec3 objects scaled by
/// the magnitude of the Vec3.
/// \param u The left hand operand of the operator
/// \param v The right hand operand of the operator
/// \returns The dot product between u and v.
double Dot(const Vec3& u, const Vec3& v);

/// The cross product of two Vec3 objects.
/// The cross product of two vectors yields a third which is mutally
/// orthogonal to the first two.
// \param u The first vector.
// \param v The second vector.
Vec3 Cross(const Vec3& u, const Vec3& v);

/// Return a unit length (length == 1.0) vector given the vector \p v.
/// \param v The vector to be resized to unit length
/// \returns A vector of unit length
/// \remark This function does not handle degenerate cases where the vector's
/// length is 0.
Vec3 UnitVector(const Vec3& v);

/// Return the reflected vector given the normal \p n and the incoming
/// direction vector \p v.
/// \param v The incoming vector direction
/// \param n The normal to the surface
/// \returns the reflection vector
Vec3 Reflect(const Vec3& v, const Vec3& n);

/// Convert a Vec3 object into a string so it can be printed.
/// This is a function which defines a new behavior for the << operator.
/// \param out An output stream such as cout
/// \param v A Vec3 object
std::ostream& operator<<(std::ostream& out, const Vec3& v);

Vec3 random_in_unit_sphere();

// A fancy C++ trick!
// Namespace aliases, see
// https://en.cppreference.com/w/cpp/language/namespace_alias

/// A 3D point and a 3D vector are very similar. For the sake of this
/// application we shall make a namespace alias so that Point3 means the
/// same thing as Vec3. (Be warned that mathematically a 3D point is not
/// the same thing as a 3D vector.)
using Point3 = Vec3;

/// A 3 channel color and a 3D vector are very similar. For the sake of this
/// application we shall make a namespace alias so that Color means the
/// same thing as Vec3. (Be warned that mathematically a 3 channel color is
/// not the same thing as a 3D vector.)
using Color = Vec3;
#endif
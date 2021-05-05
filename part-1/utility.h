
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <array>
#include <map>
#include <memory>
#include <vector>

#include "hittable.h"
#include "material.h"
#include "sphere.h"
#include "vec3.h"

/// Global variable representing positive infinity
extern const double kInfinity;
/// Global variable representing the mathematical constant 𝜋 (pi)
extern const double kPi;

/// Clamp a value \p x to be between \p min and \p max
/// \param x The value to be clamped
/// \param min The minimum value that x may be
/// \param max The maximum value that x may be
/// returns \p x, \p min, or \p max, whichever is smallest
double Clamp(double x, double min, double max);

/// Clamp all values of Vec3 \p v to be between \p min and \p max
/// \param v The Vec3 to be clamped
/// \param min The minimum value that any component of \p v may be
/// \param max The maximum value that any component of \p v may be
/// returns a new Vec3 with all the values clamped to be between min and max
Vec3 Clamp(const Vec3 v, double min, double max);

/// Square the value \p x
/// \param x a double to be squared
/// \returns x * x
double Square(double x);

/// Coverts degrees to radians
/// \param degrees Degrees
/// \returns the number of radians
double DegreesToRadians(double degrees);

/// Create a random scene of many spheres
/// \param num_elements The number of randomly created elements to place
/// in the scene
/// \returns A vector of hittable elements
std::vector<std::shared_ptr<Hittable>> RandomScene(int num_elements);

/// Return a vector with one yellow sphere that is floating in front of
/// the camera similar to lab 11.
/// \returns a vector of hittable objects which in this case only has one
/// object in it, a yello sphere.
std::vector<std::shared_ptr<Hittable>> OriginalScene();

/// Return an array of PhongMaterial objects.
/// This utility function is useful if a number of objects are being
/// created and random material properties are to be assigned. The materials
/// were taken from Mark Kilgard's
/// [teapots.c]
/// (https://www.opengl.org/archives/resources/code/samples/redbook/teapots.c)
/// program.
std::array<std::shared_ptr<PhongMaterial>, 29> make_phong_material_array();

/// Return a map (or dictionary) of PhongMaterial objects.
/// This utility function is useful to lookup material properties when
/// only the name of the material is known. The materials were taken from
/// Mark Kilgard's
/// [teapots.c]
/// (https://www.opengl.org/archives/resources/code/samples/redbook/teapots.c)
/// program.
std::map<std::string, std::shared_ptr<PhongMaterial>> make_phong_material_map();

#endif
#ifndef __MY_POINT3_H__
#define __MY_POINT3_H__

#include <cstddef>
#include <ostream>

class Point3 {
 public:
  // Constructors.
  Point3(const double x, const double y, const double z);
  Point3(const double coord[3]);
  Point3(const Point3& p);

  // Utility.
  double norm2(void) const;
  double sqnorm2(void) const;
  double euclidean_dist(const Point3& p) const;
  double dot(const Point3& p) const;
  std::string to_str(void) const;

  // Vector arithmetic.
  Point3 operator-(const Point3& p) const;
  Point3 operator+(const Point3& p) const;
  Point3 operator*(const double alpha) const;
  Point3 operator/(const double alpha) const;
  Point3 cross(const Point3& p) const;
  // TODO(nitikaaggarwal): Possibly add more utility operators.

 private:
  double _coord[3];
  const size_t K = 3;
};

#endif
